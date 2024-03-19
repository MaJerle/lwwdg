# 
# LIB_PREFIX: LWWDG
#
# This file provides set of variables for end user
# and also generates one (or more) libraries, that can be added to the project using target_link_libraries(...)
#
# Before this file is included to the root CMakeLists file (using include() function), user can set some variables:
#
# LWWDG_OPTS_FILE: If defined, it is the path to the user options file. If not defined, one will be generated for you automatically
# LWWDG_COMPILE_OPTIONS: If defined, it provide compiler options for generated library.
# LWWDG_COMPILE_DEFINITIONS: If defined, it provides "-D" definitions to the library build
#

# Custom include directory
set(LWWDG_CUSTOM_INC_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib_inc)

# Library core sources
set(lwwdg_core_SRCS 
    ${CMAKE_CURRENT_LIST_DIR}/src/lwwdg/lwwdg.c
)

# Setup include directories
set(lwwdg_include_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/src/include
    ${LWWDG_CUSTOM_INC_DIR}
)

# Register library to the system
add_library(lwwdg INTERFACE)
target_sources(lwwdg INTERFACE ${lwwdg_core_SRCS})
target_include_directories(lwwdg INTERFACE ${lwwdg_include_DIRS})
target_compile_options(lwwdg PRIVATE ${LWWDG_COMPILE_OPTIONS})
target_compile_definitions(lwwdg PRIVATE ${LWWDG_COMPILE_DEFINITIONS})

# Create config file if user didn't provide one info himself
if(NOT LWWDG_OPTS_FILE)
    message(STATUS "Using default lwwdg_opts.h file")
    set(LWWDG_OPTS_FILE ${CMAKE_CURRENT_LIST_DIR}/src/include/lwwdg/lwwdg_opts_template.h)
else()
    message(STATUS "Using custom lwwdg_opts.h file from ${LWWDG_OPTS_FILE}")
endif()
configure_file(${LWWDG_OPTS_FILE} ${LWWDG_CUSTOM_INC_DIR}/lwwdg_opts.h COPYONLY)
