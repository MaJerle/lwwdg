cmake_minimum_required(VERSION 3.22)

# Debug message
message("Exiting ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")

# Register library to the system
add_library(lwwdg INTERFACE)
target_sources(lwwdg INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/lwwdg/lwwdg.c)
target_include_directories(lwwdg INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/include)

# Debug message
message("Exiting ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")
