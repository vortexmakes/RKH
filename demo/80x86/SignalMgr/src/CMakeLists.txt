# Custom module and scripts
include($ENV{RKH_BASE}/cmake/boilerplate.cmake)
add_subdirectory(${RKH_BASE} ${CMAKE_CURRENT_BINARY_DIR}/rkh)

add_library(objlib${PROJECT_NAME} OBJECT 
    Actuator.c
    Sensor.c
    bsp.c
    main.c
)

target_link_libraries(objlib${PROJECT_NAME} PUBLIC rkh)
target_include_directories(objlib${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

foreach(variant RANGE 1 4)
    add_executable(${PROJECT_NAME}V${variant} SignalMgrV${variant}/SignalMgr.c)
    target_link_libraries(${PROJECT_NAME}V${variant} 
        objlib${PROJECT_NAME}
        m
    )
    target_include_directories(${PROJECT_NAME}V${variant} 
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    )
endforeach()
