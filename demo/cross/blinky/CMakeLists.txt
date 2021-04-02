cmake_minimum_required(VERSION 3.16)
project(Blinky LANGUAGES C)

set(RKH_CFG_FILE_PATH "src")

# Let's nicely support folders in IDEs
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(CMakePrintHelpers)

# This is here because preprocessor definitions specified with 
# add_definitions() are reproduced in Eclipse project file, but those 
# specified with target_compile_definitions() are not. So, if Eclipse 
# generator was not required, this definition would be dropped
add_definitions(-D${RKH_PLATFORM})   

add_subdirectory($ENV{RKH_BASE} ${CMAKE_CURRENT_BINARY_DIR}/rkh)

# Application's source files should be defined in a specific subdirectory
add_executable(${PROJECT_NAME} 
               main.c 
               blinky.c 
               blinky.h 
               rkhcfg.h
               bsp.h)
target_link_libraries(${PROJECT_NAME} PRIVATE rkh)
