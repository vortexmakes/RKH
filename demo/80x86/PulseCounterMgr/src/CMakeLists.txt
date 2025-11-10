# Custom module and scripts
include($ENV{RKH_BASE}/cmake/boilerplate.cmake)
add_subdirectory(${RKH_BASE} ${CMAKE_CURRENT_BINARY_DIR}/rkh)

add_executable(${PROJECT_NAME} 
    bsp.c
    main.c
    PulseCounterMgr.c
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE rkh)
