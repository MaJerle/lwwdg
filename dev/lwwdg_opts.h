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
 * Version:         v0.0.1
 */
#ifndef LWWDG_HDR_OPTS_H
#define LWWDG_HDR_OPTS_H

/* Rename this file to "lwwdg_opts.h" for your application */
#include "windows.h"
extern uint32_t sys_get_tick(void);
extern HANDLE lwwdg_mutex;

#define LWWDG_CRITICAL_SECTION_DEFINE
#define LWWDG_CRITICAL_SECTION_LOCK()
#define LWWDG_CRITICAL_SECTION_UNLOCK()
#define LWWDG_GET_TIME() sys_get_tick()

#endif /* LWWDG_HDR_OPTS_H */
