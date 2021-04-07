cmake_minimum_required(VERSION 3.16)

# Detect if RKH is being bundled, disable testsuite in that case
if (NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT BOOL TRUE)
endif()

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt"
            "and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project(rkh LANGUAGES C)

# Custom module and scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
if (NOT_SUBPROJECT)
    include(boilerplate)
endif()

# ------------------------- Options and variables -----------------------------
set(RKH_PLATFORM "Selects the RKH platform" CACHE STRING "__LNXGNU__")
option(RKH_DEV_BUILD 
       "Set to ON to enable RKH development on Linux platform" OFF)

if (RKH_DEV_BUILD)
    if (NOT RKH_PLATFORM STREQUAL "__LNXGNU__")
        message(FATAL_ERROR "Set RKH_PLATFORM to \"__LNXGNU__\" if you want to "
                "enable RKH_DEV_BUILD")
    else()
        set(DEV_BUILD "RKH development environment is enabled" ON)
    endif()
endif()

set(RKH_EXAMPLES_DIR ${RKH_BASE}/demo)
set(RKH_SOURCE_DIR ${RKH_BASE}/source)

# Print variables and options
cmake_print_variables(RKH_BASE)
cmake_print_variables(RKH_PLATFORM)
cmake_print_variables(DEV_BUILD)
cmake_print_variables(NOT_SUBPROJECT)

# ---------------------------------- Doc --------------------------------------
if (NOT_SUBPROJECT)
    include(doc)
endif()

# We need to bring-in the variables defined there to this scope
add_subdirectory(source)
