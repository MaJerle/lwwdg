# 
# This file provides set of variables for end user
# and also generates one (or more) libraries, that can be added to the project using target_link_libraries(...)
#
# Before this file is included to the root CMakeLists file (using include() function), user can set some variables:
#
# LWWDG_OPTS_DIR: If defined, it should set the folder path where options file shall be generated.
# LWWDG_COMPILE_OPTIONS: If defined, it provide compiler options for generated library.
# LWWDG_COMPILE_DEFINITIONS: If defined, it provides "-D" definitions to the library build
#

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