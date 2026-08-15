/**
 * \file            lwwdg_opts.h
 * \brief           LwWDG portable test options
 */
#ifndef LWWDG_OPTS_HDR_H
#define LWWDG_OPTS_HDR_H

#include <stdint.h>
#include <time.h>

/* Portable millisecond tick source, used only for host-based tests */
static inline uint32_t
lwwdg_test_get_tick(void) {
    return (uint32_t)(((uint64_t)clock() * 1000) / CLOCKS_PER_SEC);
}
#define LWWDG_GET_TIME() lwwdg_test_get_tick()

/* Test binary is single threaded -> no real locking is required */
#define LWWDG_CRITICAL_SECTION_DEFINE
#define LWWDG_CRITICAL_SECTION_LOCK()
#define LWWDG_CRITICAL_SECTION_UNLOCK()

#endif /* LWWDG_OPTS_HDR_H */
