cmake_minimum_required(VERSION 3.16)

# Detect if RKH is being bundled, disable testsuite in that case
if (NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT ON)
endif()

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt"
            "and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project(rkh LANGUAGES C)

# -------------------------------- Modules ------------------------------------
# Standard CMake modules
include(CMakePrintHelpers)
include(CMakeDependentOption)

# Custom module and scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(config)
include(doc)

# ------------------------- Options and variables -----------------------------
set(RKH_PLATFORM "Select the RKH platform" CACHE STRING "__LNXGNU__")
set(RKH_DEV_PLATFORM "Enable RKH platform for developing" BOOL FALSE)

if (RKH_PLATFORM STREQUAL "__LNXGNU__")
    set(RKH_DEV_PLATFORM TRUE)
endif()
    
option(RKH_USE_DOXYGEN "Add a doxygen target to generate the documentation" ON)
cmake_dependent_option(RKH_DEV_BUILD 
                       "Build tests, enable warnings, etc" ON  
                       "RKH_DEV_PLATFORM" OFF)
cmake_dependent_option(RKH_BUILD_EXAMPLES "Build code examples" ON 
                       "RKH_DEV_PLATFORM" OFF)

if (RKH_DEV_BUILD AND NOT RKH_PLATFORM STREQUAL "__LNXGNU__")
    message(FATAL_ERROR "Set RKH_PLATFORM to \"__LNXGNU__\" if you want to "
            "enable RKH_DEV_BUILD")
endif()

# Basic paths
set(RKH_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCES_DIR ${RKH_DIR}/source)
set(EXAMPLES_DIR ${RKH_DIR}/demo)

# Print variables and options
cmake_print_variables(RKH_PLATFORM)
cmake_print_variables(RKH_DEV_PLATFORM)
cmake_print_variables(RKH_DEV_BUILD)
cmake_print_variables(RKH_BUILD_EXAMPLES)

if (RKH_DEV_BUILD)
    # The RKH framework port for Linux platform requires pthread library
    set(CMAKE_THREAD_PREFER_PTHREAD ON)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

# We need to bring-in the variables defined there to this scope
add_subdirectory(source)
