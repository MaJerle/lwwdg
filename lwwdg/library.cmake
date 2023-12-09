# Library core sources
set(lwwdg_core_SRCS 
    ${CMAKE_CURRENT_LIST_DIR}/src/lwwdg/lwwdg.c
)

# Setup include directories
set(lwwdg_include_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

# Register library to the system
add_library(lwwdg INTERFACE)
target_sources(lwwdg INTERFACE ${lwwdg_core_SRCS})
target_include_directories(lwwdg INTERFACE ${lwwdg_include_DIRS})
target_compile_options(lwwdg PRIVATE ${LWWDG_COMPILE_OPTIONS})
target_compile_definitions(lwwdg PRIVATE ${LWWDG_COMPILE_DEFINITIONS})

# Create config file
if(DEFINED LWWDG_OPTS_DIR AND NOT EXISTS ${LWWDG_OPTS_DIR}/lwwdg_opts.h)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/src/include/lwwdg/lwwdg_opts_template.h ${LWWDG_OPTS_DIR}/lwwdg_opts.h COPYONLY)
endif()