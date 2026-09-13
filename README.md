# Lightweight Watchdog for embedded systems

LwWDG is a lightweight watchdog library, primarily targeting operating systems,
to watch multiple threads and reset system if one of them fails.

[Open documentation](https://docs.majerle.eu/projects/lwwdg/)

## Features

* Written in C (C11), compatible with `stdint.h` data types
* Supervises multiple independent watchdogs, each with its own timeout, tracked in a linked list
* Watchdogs can be added or removed at runtime with `lwwdg_add` and `lwwdg_remove`
* Single `lwwdg_process` call checks all registered watchdogs to decide whether the hardware watchdog can be kicked
* Optional named watchdogs with a debug callback fired once when a watchdog expires
* Function to enumerate all watchdogs currently in an expired state
* Configurable, platform-agnostic critical section macros for thread- and ISR-safe access
* Easy to use - very little platform dependency
* Written with operating systems in mind

## Contribute

Fresh contributions are always welcome. Simple instructions to proceed:

1. Fork Github repository
2. Follow [C style & coding rules](https://github.com/MaJerle/c-code-style) and use `clang-format` to format the code
3. Create a pull request to `develop` branch with new features or bug fixes

Alternatively you may:

1. Report a bug
2. Ask for a feature request
