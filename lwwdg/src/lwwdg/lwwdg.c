/**
 * \file            lwwdg.c
 * \brief           LwWDG main file
 */

/*
 * Copyright (c) 2023 Tilen MAJERLE
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of LWWDG - Lightweight watchdog for RTOS in embedded systems.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Version:         v1.0.0
 */
#include <stdint.h>
#include <string.h>
#include "lwwdg/lwwdg.h"

/* Check if WDG did expire */
#define WDG_IS_EXPIRED(_wdg_, _time_) (((_time_) - (_wdg_)->last_reload_time) > (_wdg_)->timeout)

/* Pointer to first watchdog entry */
static lwwdg_wdg_t* wdgs;

/**
 * \brief           Initialize watchdog module
 * \return          `1` on success, `0` otherwise
 */
uint8_t
lwwdg_init(void) {
    wdgs = NULL;
    return 1;
}

/**
 * \brief           Add new watchdog timer instance to internal linked list.
 * 
 * \param           wdg: Watchdog handle. Must not be local variable
 * \param           timeout: Max allowed timeout in milliseconds
 * \return          `1` on success, `0` otherwise
 */
uint8_t
lwwdg_add(lwwdg_wdg_t* wdg, uint32_t timeout) {
    uint8_t ret = 1;
    LWWDG_CRITICAL_SECTION_DEFINE;

    wdg->timeout = timeout;
    wdg->last_reload_time = LWWDG_GET_TIME();
    LWWDG_CRITICAL_SECTION_LOCK();
    /* Check if already on a list -> we don't want that */
    for (lwwdg_wdg_t* w = wdgs; w != NULL; w = w->next) {
        if (w == wdg) {
            ret = 0;
        }
    }
    if (ret) {
        /* Add to beginning of a list */
        wdg->next = wdgs;
        wdgs = wdg;
    }
    LWWDG_CRITICAL_SECTION_UNLOCK();
    return ret;
}

#if LWWDG_CFG_ENABLE_WDG_NAME || __DOXYGEN__

/**
 * \brief           Set the watchdog name for debug reasons.
 * 
 * \note            Available only when \ref LWWDG_CFG_ENABLE_WDG_NAME is enabled
 * 
 * \param           wdg: Watchdog instance
 * \param           name: Pointer to the constant string for the name.
 *                      String is not copied, rather only pointer is set
 */
void
lwwdg_set_name(lwwdg_wdg_t* wdg, const char* name) {
    wdg->name = name;
}

/**
 * \brief           Print all expired watchdogs
 * 
 * \note            \ref LWWDG_CFG_ENABLE_WDG_NAME and \ref LWWDG_CFG_WDG_NAME_ERR_DEBUG must
 *                  be enabled and implemented
 */
void
lwwdg_print_expired(void) {
    LWWDG_CRITICAL_SECTION_DEFINE;
    LWWDG_CRITICAL_SECTION_LOCK();

    for (lwwdg_wdg_t* wdg = wdgs; wdg != NULL; wdg = wdg->next) {
        if (WDG_IS_EXPIRED(wdg, time)) {
            LWWDG_CFG_WDG_NAME_ERR_DEBUG(wdg->name);
        }
    }
    LWWDG_CRITICAL_SECTION_UNLOCK();
}

#endif /* LWWDG_CFG_ENABLE_WDG_NAME || __DOXYGEN__ */

/**
 * \brief           Remove watchdog from the list
 * 
 * This function is typically used if a task
 * is killed by the scheduler. A user must manually
 * call the function and can later clean wdg memory
 * 
 * \param           wdg: Watchdog handle to remove from list
 * \return          `1` if removed, `0` otherwise
 */
uint8_t
lwwdg_remove(lwwdg_wdg_t* wdg) {
    lwwdg_wdg_t** ind;
    LWWDG_CRITICAL_SECTION_DEFINE;
    uint8_t ret = 0;

    LWWDG_CRITICAL_SECTION_LOCK();
    /* Check if watchdog exists on a list */
    ind = &wdgs; /* Get address of the first entry */
    while (*ind != NULL && *ind != wdg) {
        ind = &(*ind)->next;
    }

    /* ind should not be NULL if entry exists on linked list */
    if (ind != NULL) {
        *ind = wdg->next; /* Remove entry from the list */
    }
    LWWDG_CRITICAL_SECTION_UNLOCK();

    return ret;
}

/**
 * \brief           Reload thread watchdog
 * 
 * \note            Reload will not be successful, if there was a timeout before.
 *                  This will ensure that main thread won't reload hardware watchdog,
 *                  resulting system to reset
 * 
 * \param           wdg: Watchdog handle to reload
 * \return          `1` on success, `0` otherwise
 */
uint8_t
lwwdg_reload(lwwdg_wdg_t* wdg) {
    LWWDG_CRITICAL_SECTION_DEFINE;
    uint8_t ret = 0;

    LWWDG_CRITICAL_SECTION_LOCK();
    if (!WDG_IS_EXPIRED(wdg, LWWDG_GET_TIME())) {
        wdg->last_reload_time = time;
        ret = 1;
    }
    LWWDG_CRITICAL_SECTION_UNLOCK();
    return ret;
}

/**
 * \brief           Process and check system timers
 * 
 * Function will check all timers and will return OK,
 * if all timers are within max timeout state
 * 
 * \return          `1` if hardware watchdog can be reset,
 *                      `0` if at least one timer hasn't been reloaded
 *                      within maximum timeout
 */
uint8_t
lwwdg_process(void) {
    LWWDG_CRITICAL_SECTION_DEFINE;
    static uint32_t failed = 0;
    uint32_t time;

    if (failed) {
        return !failed;
    }

    time = LWWDG_GET_TIME();
    LWWDG_CRITICAL_SECTION_LOCK();
    for (lwwdg_wdg_t* wdg = wdgs; wdg != NULL; wdg = wdg->next) {
        if (WDG_IS_EXPIRED(wdg, time)) {
            failed = 1;
#if LWWDG_CFG_ENABLE_WDG_NAME
            LWWDG_CFG_WDG_NAME_ERR_DEBUG(wdg->name);
#else  /* LWWDG_CFG_ENABLE_WDG_NAME */
            break; /* Stop execution */
#endif /* LWWDG_CFG_ENABLE_WDG_NAME */
        }
    }
    LWWDG_CRITICAL_SECTION_UNLOCK();
    return !failed;
}
