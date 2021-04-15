cmake_minimum_required(VERSION 3.16)
project(Blinky LANGUAGES C)

# Custom module and scripts
include($ENV{RKH_BASE}/cmake/boilerplate.cmake)
add_subdirectory(${RKH_BASE} ${CMAKE_CURRENT_BINARY_DIR}/rkh)

# Application's source files should be defined in a specific subdirectory.
# The files in the application directory link RKH with the application. 
# This directory contains all application-specific files, such as 
# configuration options and source code.
add_executable(${PROJECT_NAME} 
               main.c 
               blinky.c 
               ${RKH_BASE}/demo/libbsp/platform/80x86/linux/bsp_blinky.c)

target_include_directories(${PROJECT_NAME} PRIVATE 
                           ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE rkh)
