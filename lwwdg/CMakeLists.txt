cmake_minimum_required(VERSION 3.22)

# Register library to the system
add_library(lwwdg INTERFACE)
target_sources(lwwdg INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/lwwdg/lwwdg.c)
target_include_directories(lwwdg INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/include)

# Create config file
if(DEFINED LWWDG_OPTS_DIR AND NOT EXISTS ${LWWDG_OPTS_DIR}/lwwdg_opts.h)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/src/include/lwwdg/lwwdg_opts_template.h ${LWWDG_OPTS_DIR}/lwwdg_opts.h COPYONLY)
endif()