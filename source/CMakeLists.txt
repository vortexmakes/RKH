if (RKH_DEV_BUILD)
    # The RKH framework port for Linux platform requires pthread library
    set(CMAKE_THREAD_PREFER_PTHREAD ON)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

add_library(rkh STATIC)
add_library(rkh:rkh ALIAS rkh)

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
    $<$<BOOL:RKH_DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/portable/80x86/linux_st/gnu/rkhport.c>)

target_include_directories(rkh PUBLIC 
    $<$<BOOL:RKH_DEV_BUILD>:${CMAKE_CURRENT_SOURCE_DIR}/portable/80x86/linux_st/gnu>
    ${CMAKE_CURRENT_SOURCE_DIR}/fwk/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/mempool/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/queue/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/sm/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/sma/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/tmr/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/trc/inc
    ${RKH_CONF_FILE_DIR})

target_compile_definitions(rkh PUBLIC ${RKH_PLATFORM})
target_link_libraries(rkh PRIVATE 
    $<$<BOOL:RKH_DEV_BUILD>:Threads::Threads>)
