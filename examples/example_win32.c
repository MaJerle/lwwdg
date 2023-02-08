#include "lwwdg/lwwdg.h"
#include "windows.h"
#include <stdio.h>
#include <stdlib.h>

HANDLE lwwdg_mutex;                        /* Mutex to simulate interrupt lock */
static LARGE_INTEGER freq, sys_start_time; /* Milliseconds time variable */

/**
 * \brief           Get current tick in ms from start of program
 * \return          uint32_t: Tick in ms
 */
uint32_t
sys_get_tick(void) {
    LONGLONG ret;
    LARGE_INTEGER now;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&now);
    ret = now.QuadPart - sys_start_time.QuadPart;
    return (uint32_t)((ret * 1000) / freq.QuadPart);
}

/* Task 1 */
void
task1(void* arg) {
    static lwwdg_wdg_t wdg;
    (void)arg;

    printf("%8u: Task 1 started...\r\n", (unsigned)sys_get_tick());
    lwwdg_add(&wdg, 3000);
    while (1) {
        /* Periodic reloads... */
        lwwdg_reload(&wdg);
    }
}

/* Task 1 */
void
task2(void* arg) {
    static lwwdg_wdg_t wdg;
    (void)arg;

    printf("%8u: Task 2 started...\r\n", (unsigned)sys_get_tick());
    lwwdg_add(&wdg, 5000);
    while (1) {
        /* No reload anymore... */
        Sleep(1000);
    }
}

/**
 * \brief           Example main function
 */
void
example_win32(void) {
    DWORD id;

    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&sys_start_time);

    /* Create lock for lwwdg */
    lwwdg_mutex = CreateMutex(NULL, 0, NULL);
    lwwdg_init(); /* Init library */

    /* Start other tasks */
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)task1, NULL, 0, &id);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)task2, NULL, 0, &id);

    /* Main task... */
    while (1) {
        /* Check if all tasks are OK */
        if (lwwdg_process()) {
            printf("%8u: Refreshing hardware watchdog...\r\n", (unsigned)sys_get_tick());
            /* TODO: This is where you should reload hardware watchdog */
        } else {
            printf("%8u: At least one task is out of window -> no refresh of hardware watchdog anymore...\r\n",
                   (unsigned)sys_get_tick());
        }
        Sleep(500); /* Make some sleep to offload messages in the WIN32 example */
    }
    return 0;
}