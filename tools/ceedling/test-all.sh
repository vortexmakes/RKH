#!/bin/bash -e
#

source_dir="../../source"
ceedling_dir="tools/ceedling"
#modules="fwk sm sma trc"
modules="trc"

if [ ! -d $source_dir ]; then
    echo "[ERROR] This script must be invoked from "$ceedling_dir
    exit 1
fi

currdir=$PWD
for module in $modules;
do
    echo ""
    echo "Run all test of "$module "module"
    echo "--------------------------------"
    cd $source_dir/$module
    if [ ! -e "project.yml" ]; then
        echo "[ERROR] Ceedling project not found"
    else
        sudo ceedling clean gcov:all
    fi
done

echo ""
echo "Generating code coverage report"
echo "-------------------------------"
for module in $modules;
do
    cd $currdir
    cd $source_dir/$module/test/
    submodules=(`find . -name "test_rkh*.c" -type f | sort -r | head -8 | sed 's/\.\\/test_//' | sed 's/\.c//'`)
    cd ..
    find build/gcov/out/ ! -name rkh$module*.gc* -type f | xargs sudo rm -f
done

cd ..
sudo lcov -c -d . -o ../$ceedling_dir/gcov/rkh-module.info
sudo genhtml ../$ceedling_dir/gcov/rkh-module.info -o ../$ceedling_dir/gcov/

exit 0

