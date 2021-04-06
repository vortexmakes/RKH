#
# <license>
#
# The RKH configuration can come from sources below. By default, 
# rkhcfg.h is used from current directory.
#
# 1. If RKH_CONF_FILE is set, the configuration file specified in it are used 
# as the framework configuration. RKH_CONF_FILE can be set in various ways:
#   1. In CMakeLists.txt, before calling find_package(RKH)
#   2. By passing -DRKH_CONF_FILE=<path/to/rkhcfg.h>
#   3. From the CMake variable cache
# 2. Otherwise, if RKH_CONF_FILE is set from environment.
# 3. Otherwise, rkhcfg.h is used if it exists in the current directory.

if (NOT DEFINED BOILERPLATE_WAS_INCLUDED)
    set(BOILERPLATE_WAS_INCLUDED 
        "Detects if boilerplate script was already included" TRUE)

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
    include(config)

    if (DEFINED RKH_BASE)
        set(RKH_BASE ${RKH_BASE})
        set(RKH_BASE_SRC "Cmake CLI or script")
    elseif (CACHED_RKH_BASE)
        set(RKH_BASE ${CACHED_RKH_BASE})
        set(RKH_BASE_SRC "cache")
    elseif (DEFINED ENV{RKH_BASE})
        set(RKH_BASE $ENV{RKH_BASE})
        set(RKH_BASE_SRC "environment")
    elseif (EXISTS ${CMAKE_CURRENT_LIST_DIR}/../cmake)
        get_filename_component(RKH_ABS_DIR 
                               ${CMAKE_CURRENT_LIST_DIR}/.. 
                               ABSOLUTE)
        set(RKH_BASE ${RKH_ABS_DIR})
        set(RKH_BASE_SRC "default")
    else()
        message(FATAL_ERROR "RKH base directory cannot be found")
    endif()
    get_filename_component(RKH_BASE_DIR ${RKH_BASE} DIRECTORY)
    message("RKH base directory from ${RKH_BASE_SRC} located in: ${RKH_BASE}")
    set(CACHED_RKH_BASE ${RKH_BASE} CACHE STRING 
        "Specifies the RKH directory in which it is located")
    unset(RKH_BASE CACHE)
endif()
