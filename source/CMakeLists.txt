if (DEV_BUILD)
    # The RKH framework port for Linux platform requires pthread library
    set(CMAKE_THREAD_PREFER_PTHREAD ON)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    if (NOT Threads_FOUND)
        message(FATAL_ERROR "Threads package is not found")
    endif()
endif()

add_library(rkh STATIC)
add_library(rkh:rkh ALIAS rkh)
add_library(rkh_interface INTERFACE)
add_library(rkh:rkh_interface ALIAS rkh_interface)

# Modules source files
target_sources(rkh PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/src/rkhfwk_bittbl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/src/rkhfwk_dynevt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/src/rkhfwk_evtpool.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/src/rkhfwk_pubsub.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/src/rkhfwk_rdygrp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/src/rkhfwk_sched.c
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/src/rkhfwk_version.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mempool/src/rkhmempool.c
    ${CMAKE_CURRENT_SOURCE_DIR}/queue/src/rkhqueue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sm/src/rkhsm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sma/src/rkhsma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sma/src/rkhsma_prio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/sma/src/rkhsma_sync.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tmr/src/rkhtmr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trc/src/rkhtrc_filter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trc/src/rkhtrc_record.c
    ${CMAKE_CURRENT_SOURCE_DIR}/trc/src/rkhtrc_stream.c)

# Platform dependent source files used by demo applications
target_sources(rkh PRIVATE 
    $<$<BOOL:${DEV_BUILD}>:
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/80x86/linux_st/gnu/rkhport.c>)

# Global includes. Used by all targets
target_include_directories(rkh_interface INTERFACE
    $<BUILD_INTERFACE:$<$<BOOL:${DEV_BUILD}>:${CMAKE_CURRENT_SOURCE_DIR}/portable/80x86/linux_st/gnu>>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fwk/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mempool/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/queue/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sm/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/sma/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tmr/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/trc/inc>
    $<BUILD_INTERFACE:${RKH_CONF_FILE_DIR}>)

target_compile_definitions(rkh_interface 
                           INTERFACE 
                           $<IF:$<BOOL:${NOT_FIND_PACKAGE}>,${RKH_PLATFORM},__PLAT_DEF_BY_BUILD__>)

# Link required libraries
target_link_libraries(rkh PUBLIC rkh_interface)
target_link_libraries(rkh PRIVATE $<$<BOOL:${DEV_BUILD}>:Threads::Threads>)

if (DEV_BUILD) 
    add_subdirectory(../demo/libbsp ${CMAKE_CURRENT_BINARY_DIR}/bsp)
    target_link_libraries(rkh PUBLIC bsp)
endif()

# Introduce variables:
# * CMAKE_INSTALL_LIBDIR
# * CMAKE_INSTALL_BINDIR
# * CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

# Layout. This works for all platforms:
#   * <prefix>/lib*/cmake/<PROJECT-NAME>
#   * <prefix>/lib*/
#   * <prefix>/include/
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(VERSION_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(PROJECT_CONFIG "${GENERATED_DIR}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${VERSION_CONFIG}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "${RKH_BASE}/cmake/Config.cmake.in"
    "${PROJECT_CONFIG}"
    INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}"
)

# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS rkh rkh_interface bsp
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
#   * Source/foo/Baz.hpp -> <prefix>/include/foo/Baz.hpp
install(
   DIRECTORY 
   portable/80x86/linux_st/gnu/
   fwk/inc/
   mempool/inc/
   queue/inc/
   sm/inc/
   sma/inc/
   tmr/inc/
   trc/inc/
   $<$<BOOL:${DEV_BUILD}>:../demo/libbsp/platform/80x86/linux/>
   $<$<BOOL:${DEV_BUILD}>:../demo/libbsp/common/>
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
   FILES_MATCHING PATTERN "*.h"
)

install(
    FILES ${RKH_CONF_FILE_DIR}/rkhcfg.h
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES "${PROJECT_CONFIG}" "${VERSION_CONFIG}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${CONFIG_INSTALL_DIR}"
)
