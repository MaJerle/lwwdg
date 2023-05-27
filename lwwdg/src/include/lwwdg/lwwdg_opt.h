/**
 * \file            lwwdg_opt.h
 * \brief           LwWDG options
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
#ifndef LWWDG_OPT_HDR_H
#define LWWDG_OPT_HDR_H

/* Uncomment to ignore user options (or set macro in compiler flags) */
/* #define LWWDG_IGNORE_USER_OPTS */

/* Include application options */
#ifndef LWWDG_IGNORE_USER_OPTS
#include "lwwdg_opts.h"
#endif /* LWWDG_IGNORE_USER_OPTS */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        LWWDG_OPT Configuration
 * \brief           Default configuration setup
 * \{
 */

/**
 * \brief           Enables or disables field in wdg structure to contain 
 *                  watchdog name.
 * 
 * This can be useful for debugging purposes
 */
#ifndef LWWDG_CFG_ENABLE_WDG_NAME
#define LWWDG_CFG_ENABLE_WDG_NAME 0
#endif

/**
 * \brief           Macro called if \ref LWWDG_CFG_ENABLE_WDG_NAME is enabled
 *                  and if watchdog error occurs.
 * 
 * It can be overwritten by the application to print watchdog name. 
 * 
 * \param[in]       _wdg_name_: Watchdog name as defined by \ref lwwdg_set_name function
 */
#ifndef LWWDG_CFG_WDG_NAME_ERR_DEBUG
#define LWWDG_CFG_WDG_NAME_ERR_DEBUG(_wdg_name_)
#endif

/**
 * \brief           Get system time in milliseconds.
 * 
 * It is required to keep reload time
 */
#ifndef LWWDG_GET_TIME
#error "LWWDG_GET_TIME() must be defined in user lwwdg_opts.h file or as global macro"
#define LWWDG_GET_TIME()
#endif

/**
 * \brief           Define the critical section
 * 
 * Used at the beinning of the function, to define potential local
 * variable to keep status of critical section (if already locked)
 * 
 * \note            Default implementation is for *Cortex-M*
 */
#ifndef LWWDG_CRITICAL_SECTION_DEFINE
#define LWWDG_CRITICAL_SECTION_DEFINE uint32_t primask
#endif

/**
 * \brief           Lock the critical section.
 * 
 * Critical section should prevent other tasks or interrupt,
 * to access to the same core.
 * 
 * Easiest is to simply disable the interrupt, since task is normally pretty quick.
 * 
 * \note            Default implementation is for *Cortex-M*
 */
#ifndef LWWDG_CRITICAL_SECTION_LOCK
#define LWWDG_CRITICAL_SECTION_LOCK()                                                                                  \
    do {                                                                                                               \
        primask = __get_PRIMASK();                                                                                     \
        __disable_IRQ();                                                                                               \
    } while (0)
#endif

/**
 * \brief           Unlock the critical section.
 * 
 * \note            Default implementation is for *Cortex-M*
 */
#ifndef LWWDG_CRITICAL_SECTION_UNLOCK
#define LWWDG_CRITICAL_SECTION_UNLOCK() __set_PRIMASK(primask)
#endif

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWWDG_OPT_HDR_H */
