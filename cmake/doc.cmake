#
# <license>
#
# Add a make target 'doc' to generate RKH documentation with Doxygen.
# Doxygen options must be in the file 'Doxyfile.in'.

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile 
                   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
#   add_custom_target(doc
#       ${DOXYGEN_EXECUTABLE} 
#       ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile > doxygen.log
#       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#       COMMENT "${BoldMagenta}Generating API documentation with Doxygen "
#       "(open ./html/index.html to view).${ColourReset}"
#       VERBATIM
#   )
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    set(DOXY_LOG ${CMAKE_CURRENT_BINARY_DIR}/doxygen.log)
    set(ARGS ${DOXYFILE_OUT})

    add_custom_target(doc
        ${CMAKE_COMMAND}
        -DCOMMAND=${DOXYGEN_EXECUTABLE}
        -DARGS="${ARGS}"
        -DOUTPUT_FILE=${DOXY_LOG}
        -DERROR_FILE=${DOXY_LOG}
        -DWORKING_DIRECTORY=${CMAKE_CURRENT_BINARY_DIR}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/execute_process.cmake
    )
endif(DOXYGEN_FOUND)
