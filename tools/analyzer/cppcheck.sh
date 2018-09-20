#!/bin/bash -e
#
#   cppcheck - Tool for static C/C++ code analysis
#   site: http://cppcheck.sourceforge.net/
#
#   usage:
#   cppcheck --language=c --enable=performance,information,missingInclude \
#   -D__TEST__ -I../demo/cross/blinky -Iportable/test/ -Ifwk/inc 
#   -Imempool/inc -Iqueue/inc -Ism/inc -Isma/inc -Itmr/inc -Itrc/inc 
#   fwk/src/rkhfwk_*.c mempool/src/rkhmempool.c queue/src/rkhqueue.c 
#   sm/src/rkhsm.c sma/src/rkhsma.c tmr/src/rkhtmr.c trc/src/rkhtrc_*.c
#

source_dir="../../source"
cppcheck_dir="tools/analyzer"
modules="fwk mempool queue sm sma tmr trc"
additional="../demo/cross/blinky portable/test/"
flags="--quiet --error-exitcode=1 --language=c --enable=performance,information,missingInclude"
defines="__TEST__"

#echo $PATH
#export PATH="$PATH:/home/travis/.rvm/gems/ruby-2.4.1/bin"
#echo $PATH
#which ceedling
#exit 0

if [ ! -d $source_dir ]; then
    echo "[ERROR] This script must be invoked from "$uno_dir
    exit 1
fi

currdir=$PWD
includes=()
sources=()
for module in $modules;     # Added include files of every module
do
    includes+=(-I$module/inc)
    sources+=($module/src/rkh$module*.c)
done
for file in $additional;    # Added additional include files
do
    includes+=(-I$file)
done

cd $source_dir
files="${sources[@]}"
cppcheck $flags -D$defines "${includes[@]}" $files

