/**
 * \file            lwwdg.h
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
 * Version:         v0.0.1
 */
#ifndef LWWDG_HDR_H
#define LWWDG_HDR_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include "lwwdg/lwwdg_opt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        LWWDG Lightweight watchdog for RTOS in embedded systems
 * \brief           Lightweight watchdog for RTOS in embedded systems
 * \{
 */

/**
 * \brief           Watchdog structure
 * 
 */
typedef struct lwwdg_wdg {
    struct lwwdg_wdg* next;    /*!< Next entry on a list */
    uint32_t timeout;          /*!< Timeout in milliseconds */
    uint32_t last_reload_time; /*!< Last reload time in milliseconds */
} lwwdg_wdg_t;

uint8_t lwwdg_init(void);
uint8_t lwwdg_add(lwwdg_wdg_t* wdg, uint32_t timeout);
uint8_t lwwdg_remove(lwwdg_wdg_t* wdg);
uint8_t lwwdg_reload(lwwdg_wdg_t* wdg);
uint8_t lwwdg_process(void);

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWWDG_HDR_H */
