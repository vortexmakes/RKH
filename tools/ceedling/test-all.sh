#!/bin/bash -e
#

source_dir="../../source"
ceedling_dir="tools/ceedling"
modules="fwk mempool queue sm sma tmr trc"

if [ ! -d $source_dir ]; then
    echo "[ERROR] This script must be invoked from "$ceedling_dir
    exit 1
fi

for module in $modules;
do
    echo "Run all test of "$module "module"
    echo "--------------------------------"
    cd $source_dir/$module
    if [ ! -e "project.yml" ]; then
        echo "[ERROR] Ceedling project not found"
    else
        ceedling clean gcov:all utils:gcov
    fi
done

exit 0

