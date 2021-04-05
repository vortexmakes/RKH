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
    ${SOURCES_DIR}/fwk/src/rkhfwk_bittbl.c
    ${SOURCES_DIR}/fwk/src/rkhfwk_dynevt.c
    ${SOURCES_DIR}/fwk/src/rkhfwk_evtpool.c
    ${SOURCES_DIR}/fwk/src/rkhfwk_pubsub.c
    ${SOURCES_DIR}/fwk/src/rkhfwk_rdygrp.c
    ${SOURCES_DIR}/fwk/src/rkhfwk_sched.c
    ${SOURCES_DIR}/fwk/src/rkhfwk_version.c
    ${SOURCES_DIR}/mempool/src/rkhmempool.c
    ${SOURCES_DIR}/queue/src/rkhqueue.c
    ${SOURCES_DIR}/sm/src/rkhsm.c
    ${SOURCES_DIR}/sma/src/rkhsma.c
    ${SOURCES_DIR}/sma/src/rkhsma_prio.c
    ${SOURCES_DIR}/sma/src/rkhsma_sync.c
    ${SOURCES_DIR}/tmr/src/rkhtmr.c
    ${SOURCES_DIR}/trc/src/rkhtrc_filter.c
    ${SOURCES_DIR}/trc/src/rkhtrc_record.c
    ${SOURCES_DIR}/trc/src/rkhtrc_stream.c)

# BSP source files used by demo applications
target_sources(rkh PRIVATE 
    ${EXAMPLES_DIR}/libbsp/platform/80x86/linux/assert.c
    ${EXAMPLES_DIR}/libbsp/platform/80x86/linux/getopt.c
    ${EXAMPLES_DIR}/libbsp/platform/80x86/linux/hook.c
    ${EXAMPLES_DIR}/libbsp/platform/80x86/linux/trace_io.c
    ${EXAMPLES_DIR}/libbsp/platform/80x86/linux/trace_io_tcp.c)
    
target_sources(rkh PRIVATE 
               $<$<BOOL:RKH_DEV_BUILD>:
               ${SOURCES_DIR}/portable/80x86/linux_st/gnu/rkhport.c>)

target_include_directories(rkh PUBLIC 
                           ${SOURCES_DIR}/portable/80x86/linux_st/gnu
                           ${EXAMPLES_DIR}/libbsp/platform/80x86/linux
                           ${EXAMPLES_DIR}/libbsp/common
                           ${SOURCES_DIR}/fwk/inc
                           ${SOURCES_DIR}/mempool/inc
                           ${SOURCES_DIR}/queue/inc
                           ${SOURCES_DIR}/sm/inc
                           ${SOURCES_DIR}/sma/inc
                           ${SOURCES_DIR}/tmr/inc
                           ${SOURCES_DIR}/trc/inc
                           ${RKH_CONF_FILE_DIR})

target_compile_definitions(rkh PUBLIC ${RKH_PLATFORM})
target_link_libraries(rkh PRIVATE 
                      $<$<BOOL:RKH_DEV_BUILD>:Threads::Threads>)
