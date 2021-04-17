add_library(bsp STATIC)

target_sources(bsp PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/assert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/getopt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/hook.c
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/trace_io.c
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/trace_io_tcp.c)
    
target_include_directories(bsp PUBLIC 
    $<BUILD_INTERFACE:$<$<BOOL:${DEV_BUILD}>:${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux>>
    $<BUILD_INTERFACE:$<$<BOOL:${DEV_BUILD}>:${CMAKE_CURRENT_SOURCE_DIR}/common>>)
    
target_link_libraries(bsp PRIVATE rkh_interface)
