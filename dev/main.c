#include <stdio.h>
#include <windows.h>
#include "lwwdg/lwwdg.h"

extern void example_win32(void);

int
main(void) {
    example_win32();
    return 0;
}
