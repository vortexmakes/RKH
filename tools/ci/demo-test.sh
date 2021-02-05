#!/bin/bash
#
#   This script builds and executes a demo application for x86/linux/gnu 
#   platform in order to check either the building result and the application 
#   output. If these tests are correct this script will return '0', otherwise 
#   it will return '1'
#

buildDirPath=$1
appName="blinky"
traceOutFile="trout"
appOutFile="out"
pattern="LED\sON\sLED\sOFF\sLED\sON"
cnt=8

if [ ! -d $buildDirPath ]; then
    echo "[ERROR] Cannot find $buildDirPath directory"
    exit 1
fi

# Build application
cd $buildDirPath
make 2> /dev/null

if [ $? != '0' ]; then
    echo "[ERROR] Building the application, an error happened ($?)"
    exit 1
elif [ ! -x $buildDirPath/$appName ]; then
    echo "[ERROR] Cannot execute $appName because it does not exist"
    exit 1
fi

# Execute application
nohup stdbuf -oL ./$appName -f $traceOutFile > $appOutFile &
for cnt in {1..4}
do
    sleep 2;
    jobs -l
done

kill -9 $(pidof $appName)
grep -qz $pattern $appOutFile

if [ $? != '0' ]; then
    echo "[ERROR] Expected application output is not found"
    exit 1
fi

exit 0
