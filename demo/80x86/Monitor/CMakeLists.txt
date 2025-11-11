cmake_minimum_required(VERSION 3.16)
project(Monitor LANGUAGES C)

if (NOT DEFINED ENV{RKH_BASE})
    message(FATAL_ERROR "RKH_BASE is not defined in the environment. "
                        "Define it using 'export RKH_BASE=<path/to/RKH>', "
                        "before executing CMake")
endif()

add_subdirectory(src)
