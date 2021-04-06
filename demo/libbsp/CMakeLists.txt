add_library(bsp STATIC)
add_library(bsp:bsp ALIAS bsp)

target_sources(bsp PRIVATE 
    $<$<BOOL:RKH_DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/assert.c>
    $<$<BOOL:RKH_DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/getopt.c>
    $<$<BOOL:RKH_DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/hook.c>
    $<$<BOOL:RKH_DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/trace_io.c>
    $<$<BOOL:RKH_DEV_BUILD>:
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux/trace_io_tcp.c>)
    
target_include_directories(bsp PUBLIC 
    $<$<BOOL:RKH_DEV_BUILD>:${CMAKE_CURRENT_SOURCE_DIR}/platform/80x86/linux> 
    $<$<BOOL:RKH_DEV_BUILD>:${CMAKE_CURRENT_SOURCE_DIR}/common>)

target_compile_definitions(bsp PUBLIC ${RKH_PLATFORM})
target_link_libraries(bsp PRIVATE rkh)
