cmake_minimum_required(VERSION 3.16)

# Detect if RKH is being bundled
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
    include(version)
    set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
    configure_file(${RKH_BASE}/cmake/rkhfwk_version.h.in
                   ${GENERATED_DIR}/rkhfwk_version.h)
    file(COPY ${GENERATED_DIR}/rkhfwk_version.h
         DESTINATION ${RKH_BASE}/source/fwk/inc)
endif()

# Set environment to develop the RKH framework, if it is needed
set(RKH_PLATFORM "__LNXGNU__" CACHE STRING "Selects the RKH platform")
option(RKH_DEV_BUILD 
       "Set to ON to enable RKH development on Linux platform" OFF)
if (RKH_DEV_BUILD)
    if (NOT RKH_PLATFORM STREQUAL "__LNXGNU__")
        message(FATAL_ERROR "Set RKH_PLATFORM to \"__LNXGNU__\" if you want to "
                "enable RKH_DEV_BUILD")
    else()
        set(DEV_BUILD ON CACHE BOOL "RKH development platform is enabled")
    endif()
endif()

set(NOT_FIND_PACKAGE FALSE CACHE BOOL "RKH project is being bundle")

# Print fundamental variables and options
cmake_print_variables(RKH_BASE)
cmake_print_variables(RKH_PLATFORM)
cmake_print_variables(DEV_BUILD)
cmake_print_variables(NOT_SUBPROJECT)
cmake_print_variables(NOT_FIND_PACKAGE)

# We need to bring-in the variables defined there to this scope
add_subdirectory(source)

# Generate documentation
if (NOT_SUBPROJECT)
    add_subdirectory(doc)
endif()

# Run unit tests
if (NOT_SUBPROJECT)
    include(unittest)
endif()
