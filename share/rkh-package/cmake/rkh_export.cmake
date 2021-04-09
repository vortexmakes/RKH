# The purpose of this CMake file is to register a rkhConfig package reference 
# in: Unix/Linux/MacOS: ~/.cmake/packages/rkh
#
# Having rkhConfig package allows for find_package(rkh) to work when RKH_BASE 
# is not defined. 
# Create the reference by running `cmake -P rkh_export.cmake` in this directory.

set(MD5_INFILE "current_path.txt")

# We write CMAKE_CURRENT_LIST_DIR into MD5_INFILE, as the content of that 
# file will be used for MD5 calculation.
# This means we effectively get the MD5 of CMAKE_CURRENT_LIST_DIR which must 
# be used for CMake user package registry.
file(WRITE ${CMAKE_CURRENT_LIST_DIR}/${MD5_INFILE} ${CMAKE_CURRENT_LIST_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E 
                md5sum ${CMAKE_CURRENT_LIST_DIR}/${MD5_INFILE}
                OUTPUT_VARIABLE MD5_SUM
)
string(SUBSTRING ${MD5_SUM} 0 32 MD5_SUM)
file(WRITE 
     $ENV{HOME}/.cmake/packages/rkh/${MD5_SUM} 
     ${CMAKE_CURRENT_LIST_DIR})

message("RKH (${CMAKE_CURRENT_LIST_DIR})")
message("has been added to the user package registry in: "
        "~/.cmake/packages/rkh\n")

file(REMOVE ${CMAKE_CURRENT_LIST_DIR}/${MD5_INFILE})
