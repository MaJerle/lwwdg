#include <stdio.h>
#include <stdlib.h>
#include "lwwdg/lwwdg.h"

#define TEST_RUN(cond)                                                                                                 \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            printf("Test failed on the line %u\r\n", (unsigned)__LINE__);                                              \
            return -1;                                                                                                 \
        }                                                                                                              \
    } while (0)

int
test_run(void) {
    uint8_t ret = 0;
    static lwwdg_wdg_t wdg1, wdg2, wdg3;

    printf("Test started\r\n");

    ret = lwwdg_init();
    TEST_RUN(ret > 0);

    /* Add watchdogs to the list */
    ret = lwwdg_add(&wdg1, 1000);
    TEST_RUN(ret > 0);
    ret = lwwdg_add(&wdg1, 1000);
    TEST_RUN(ret == 0);
    ret = lwwdg_add(&wdg1, 0);
    TEST_RUN(ret == 0);
    ret = lwwdg_add(&wdg2, 1000);
    TEST_RUN(ret > 0);
    ret = lwwdg_add(&wdg3, 1000);
    TEST_RUN(ret > 0);

    /* Remove watchdogs here */
    ret = lwwdg_remove(&wdg1);
    TEST_RUN(ret > 0);
    ret = lwwdg_remove(&wdg1);
    TEST_RUN(ret == 0);
    ret = lwwdg_remove(&wdg2);
    TEST_RUN(ret > 0);
    ret = lwwdg_remove(&wdg3);
    TEST_RUN(ret > 0);

    printf("Test completed\r\n");

    return 0;
}
