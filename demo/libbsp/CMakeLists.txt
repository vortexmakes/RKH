add_library(bsp STATIC)
add_library(bsp:bsp ALIAS bsp)

target_sources(bsp PRIVATE 
    $<$<BOOL:DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/assert.c>
    $<$<BOOL:DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/getopt.c>
    $<$<BOOL:DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/hook.c>
    $<$<BOOL:DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/trace_io.c>
    $<$<BOOL:DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/trace_io_tcp.c>)
    
target_include_directories(bsp PUBLIC 
    $<$<BOOL:DEV_BUILD>:${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux> 
    $<$<BOOL:DEV_BUILD>:${CMAKE_CURRENT_SOURCE_DIR}/common>)

target_link_libraries(bsp PRIVATE rkhif)
