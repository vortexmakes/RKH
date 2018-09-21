#!/bin/bash -e
#

#uno -l -w -e -D__TEST__ -Ifwk/inc/ -Isma/inc -Ism/inc -Itrc/inc -Imempool/inc -Iqueue/inc -Itmr/inc -I../demo/cross/blinky -Iportable/test/ fwk/src/rkhfwk_*.c mempool/src/rkhmempool.c queue/src/rkhqueue.c sm/src/rkhsm.c sma/src/rkhsma*.c tmr/src/rkhtmr.c trc/src/rkhtrc_*.c
#uno: trc/src/rkhtrc_stream.c:  79 possible array indexing error 'trcstm[128]' (array-size: 128)
#uno:    check completed, try 'uno -h' for different checks

source_dir="../../source"
uno_dir="tools/analyzer"
modules="fwk mempool queue sm sma tmr trc"
additional="../demo/cross/blinky portable/test/"
flags="-l"
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

# Build and install
cf='-DPC -ansi -Wall -ggdb -DCPP="\\"gcc -E\\"" -DBINDIR=\\"$(BINDIR)\\"'

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
uno $flags -D$defines "${includes[@]}" "${sources[@]}"

exit 0

