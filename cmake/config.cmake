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

include(CMakePrintHelpers)

if (DEFINED RKH_CONF_FILE)
    set(RKH_CONF_FILE ${RKH_CONF_FILE})
    set(CONF_FILE_SRC "Cmake CLI or script")
elseif (CACHED_RKH_CONF_FILE)
    set(RKH_CONF_FILE ${CACHED_RKH_CONF_FILE})
    set(CONF_FILE_SRC "cache")
elseif (DEFINED ENV{RKH_CONF_FILE})
    set(RKH_CONF_FILE $ENV{RKH_CONF_FILE})
    set(CONF_FILE_SRC "environment")
elseif (EXISTS ${CMAKE_SOURCE_DIR}/rkhcfg.h)
    set(RKH_CONF_FILE ${CMAKE_SOURCE_DIR}/rkhcfg.h)
    set(CONF_FILE_SRC "default")
elseif (EXISTS ${CMAKE_SOURCE_DIR}/src/rkhcfg.h)
    set(RKH_CONF_FILE ${CMAKE_SOURCE_DIR}/src/rkhcfg.h)
    set(CONF_FILE_SRC "default (src)")
else()
    message(FATAL_ERROR "Configuration file rkhcfg.h cannot be found")
endif()

get_filename_component(RKH_CONF_FILE_NAME ${RKH_CONF_FILE} NAME)
get_filename_component(RKH_CONF_FILE_DIR ${RKH_CONF_FILE} DIRECTORY)
if (NOT ${RKH_CONF_FILE_NAME} MATCHES "rkhcfg.h")
    message(FATAL_ERROR "Configuration file must be called rkhcfg.h")
elseif (NOT IS_ABSOLUTE ${RKH_CONF_FILE_DIR})
    set(RKH_CONF_FILE_DIR 
        ${CMAKE_CURRENT_SOURCE_DIR}/${RKH_CONF_FILE_DIR})
endif()

message(STATUS "Configuration file (rkhcfg.h) from ${CONF_FILE_SRC} is "
        "located in: ${RKH_CONF_FILE_DIR}")
set(CACHED_RKH_CONF_FILE ${RKH_CONF_FILE} CACHE STRING 
    "Specifies the RKH configuration file, which is used to build RKH")
unset(RKH_CONF_FILE CACHE)
variable_watch(RKH_CONF_FILE)
