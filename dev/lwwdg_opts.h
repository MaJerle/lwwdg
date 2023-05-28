/**
 * \file            lwwdg_opts_template.h
 * \brief           LwWDG configuration file
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
 * Version:         v1.1.1
 */
#ifndef LWWDG_HDR_OPTS_H
#define LWWDG_HDR_OPTS_H

#include <stdio.h>

/* Win32 port */
#include "windows.h"
extern uint32_t sys_get_tick(void);   /* Milliseconds tick is available externally */
extern HANDLE lwwdg_mutex;            /* Mutex is defined and initialized externally */

#define LWWDG_CRITICAL_SECTION_DEFINE /* Nothing to do here... */
#define LWWDG_CRITICAL_SECTION_LOCK()                                                                                  \
    do {                                                                                                               \
        WaitForSingleObject(lwwdg_mutex, INFINITE);                                                                    \
    } while (0)
#define LWWDG_CRITICAL_SECTION_UNLOCK()     ReleaseMutex(lwwdg_mutex)
#define LWWDG_GET_TIME()                    sys_get_tick()

#define LWWDG_CFG_ENABLE_WDG_NAME           1
#define LWWDG_CFG_WDG_NAME_ERR_DEBUG(_wdg_) printf("Watchdog %s failed to reload in time!\r\n", (_wdg_))

#endif /* LWWDG_HDR_OPTS_H */
