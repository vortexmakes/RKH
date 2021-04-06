cmake_minimum_required(VERSION 3.16)
project(Blinky LANGUAGES C)

# Let's nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# This is here because preprocessor definitions specified with 
# add_definitions() are reproduced in Eclipse project file, but those 
# specified with target_compile_definitions() are not. So, if Eclipse 
# generator was not required, this definition would be dropped
#add_definitions(-D${RKH_PLATFORM})   

# Custom module and scripts
include($ENV{RKH_BASE}/cmake/boilerplate.cmake)

add_subdirectory(${RKH_BASE} ${CMAKE_CURRENT_BINARY_DIR}/rkh)
add_subdirectory(${RKH_BASE}/demo/libbsp ${CMAKE_CURRENT_BINARY_DIR}/bsp)

# Application's source files should be defined in a specific subdirectory
add_executable(${PROJECT_NAME} 
               main.c 
               blinky.c 
               ${RKH_BASE}/demo/libbsp/platform/80x86/linux/bsp_blinky.c 
               blinky.h 
               rkhcfg.h
               bsp.h)

target_link_libraries(${PROJECT_NAME} PRIVATE rkh)
target_link_libraries(${PROJECT_NAME} PRIVATE bsp)
