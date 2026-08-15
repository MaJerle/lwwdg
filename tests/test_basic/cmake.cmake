# CMake include file

# Add more sources
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/test_basic.c
)

# Options file
set(LWWDG_OPTS_FILE ${CMAKE_CURRENT_LIST_DIR}/lwwdg_opts.h)
