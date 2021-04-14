#
#

find_program(CEEDLING ceedling)
if(${CEEDLING} STREQUAL CEEDLING-NOTFOUND)
    message(FATAL_ERROR 
            "The 'ceedling' program was not found. Make sure you have it"
            "installed.")
endif()

find_program(LCOV lcov)
if(${LCOV} STREQUAL LCOV-NOTFOUND)
    message(FATAL_ERROR 
            "The 'lcov' program was not found. Make sure you have it"
            "installed.")
endif()

find_program(GCOV gcov)
if(${GCOV} STREQUAL GCOV-NOTFOUND)
    message(FATAL_ERROR 
            "The 'gcov' program was not found. Make sure you have it"
            "installed.")
endif()

if(DEFINED CEEDLING AND DEFINED LCOV AND DEFINED GCOV)
    # Get ceedling version
    execute_process(COMMAND ceedling version
        OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE version)
    string(REGEX MATCH "Ceedling:: ([0-9]*.[0-9]*.[0-9]*)" _ ${version})
    set(CEEDLING_VERSION ${CMAKE_MATCH_1})
    message(STATUS "Ceedling: ${CEEDLING} "
            "(ceedling version: \"${CEEDLING_VERSION}\")")

    # Get lcov version
    execute_process(COMMAND lcov --version 
        OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE version)
    string(REGEX MATCH "LCOV version ([0-9]*.[0-9]*.[0-9]*)" _ ${version})
    set(LCOV_VERSION ${CMAKE_MATCH_1})
    message(STATUS "lcov: ${LCOV} (lcov --version: \"${LCOV_VERSION}\")")
else()
    message(STATUS "ceedling or lcov: not found")
endif()

set(TESTALL_LOG ${CMAKE_CURRENT_BINARY_DIR}/testall.log)
set(TESTALL_RUN_TSTAMP ${CMAKE_CURRENT_BINARY_DIR}/last_testall_run_tstamp)

# Create timestamp first so we re-run if source files are edited while
# testall is running
add_custom_command(
  OUTPUT ${TESTALL_RUN_TSTAMP}
  COMMAND cmake -E touch ${TESTALL_RUN_TSTAMP}
  COMMAND ${CMAKE_COMMAND}
    -DCOMMAND=sudo
    -DARGS=./test-all.sh
#   -DCOMMAND=./test-all.sh
    -DOUTPUT_FILE=${TESTALL_LOG}
    -DERROR_FILE=${TESTALL_LOG}
    -DWORKING_DIRECTORY=${RKH_BASE}/tools/ceedling
    -P ${RKH_BASE}/cmake/execute_process.cmake
  DEPENDS source
  COMMENT "Running test-all.sh"
  VERBATIM
)

add_custom_target(testall DEPENDS ${TESTALL_RUN_TSTAMP})
