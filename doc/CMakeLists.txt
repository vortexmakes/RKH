#
# <license>
#

find_package(Doxygen REQUIRED)

# Set Doxyfile options
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
               ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(DOXY_LOG ${CMAKE_CURRENT_BINARY_DIR}/doxygen.log)
set(ARGS ${DOXYFILE_OUT})

file(GLOB_RECURSE  DOXY_SOURCES
    ${RKH_BASE}/source/fwk/*.h
    ${RKH_BASE}/source/mempool/*.h
    ${RKH_BASE}/source/queue/*.h
    ${RKH_BASE}/source/sm/*.h
    ${RKH_BASE}/source/sma/*.h
    ${RKH_BASE}/source/tmr/*.h
    ${RKH_BASE}/source/trc/*.h
    ${RKH_BASE}/source/sma/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${RKH_BASE}/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm3/lpcx-1769/lpcxpresso/*.txt 
    ${RKH_BASE}/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm4f/frdm-k64f/kds/*.txt
    ${RKH_BASE}/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm4f/twr_k60/*.txt
    ${RKH_BASE}/demo/cross/blinky/build/arm-cortex/rkhs/arm_cm0/frdm-kl25z/cw_v10/*.txt
    ${RKH_BASE}/demo/cross/blinky/build/cfv1/rkhs/cw6_3/*.txt
    ${RKH_BASE}/demo/cross/blinky/build/s08/rkhs/cw6_3/*.txt
    ${RKH_BASE}/demo/cross/shared/build/arm-cortex/ksdk_os/ucosiii/frdm-k64f/kds/*.txt
    ${RKH_BASE}/demo/cross/shared/build/arm-cortex/rkhs/ksdk_bm/frdmk64f/kds/*.txt
    ${RKH_BASE}/third-party/utrazer/test_*.c
    ${RKH_BASE}/third-party/utrazer/test_runners/test_*.c
    ${RKH_BASE}/third-party/unitrazer/unitrazer.h
    ${RKH_BASE}/source/fwk/test/test_rkhfwk_*.c
    ${RKH_BASE}/source/sma/test/test_rkhsma*.c
    ${RKH_BASE}/source/trc/test/test_rkhtrc_*.c
    ${RKH_BASE}/source/sm/test/test_rkhsm.c)

set(DOXY_RUN_TSTAMP ${CMAKE_CURRENT_BINARY_DIR}/last_doxy_run_tstamp)

# Create timestamp first so we re-run if source files are edited while
# doxygen is running
add_custom_command(
  OUTPUT ${DOXY_RUN_TSTAMP}
  COMMAND cmake -E touch ${DOXY_RUN_TSTAMP}
  COMMAND ${CMAKE_COMMAND}
    -DCOMMAND=${DOXYGEN_EXECUTABLE}
    -DARGS="${ARGS}"
    -DOUTPUT_FILE=${DOXY_LOG}
    -DERROR_FILE=${DOXY_LOG}
    -DWORKING_DIRECTORY=${CMAKE_CURRENT_SOURCE_DIR}
    -P ${RKH_BASE}/cmake/execute_process.cmake
  DEPENDS ${DOXY_SOURCES}
  COMMENT "Running ${DOXYGEN_EXECUTABLE}"
)

add_custom_target(doxygen DEPENDS ${DOXY_RUN_TSTAMP})
