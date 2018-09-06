#!/bin/bash -e
#

source_dir="../../source"
ceedling_dir="tools/ceedling"
modules="fwk sm sma trc"

if [ ! -d $source_dir ]; then
    echo "[ERROR] This script must be invoked from "$ceedling_dir
    exit 1
fi

case "$1" in
    clean)
        clobber=1
        ;;
    *)
        clobber=0
        ;;
esac

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
         if [ $clobber == 0 ]; then
             sudo ceedling clean gcov:all
         else
             sudo ceedling clean clobber gcov:all
         fi
     fi
done

echo ""
echo "Generating code coverage report"
echo "-------------------------------"
cd ..
sudo lcov -c -d . -o ../$ceedling_dir/gcov/rkh-coverage-total.info
add=()
for module in $modules;
do
    cd $currdir
    cd $source_dir/$module
    sudo lcov -e ../../$ceedling_dir/gcov/rkh-coverage-total.info "$(pwd)/src/rkh$module*.c" -o ../../$ceedling_dir/gcov/$module.info
    add+=(-a $module".info")
#   cd $source_dir/$module/test/
#   submodules=(`find . -name "test_rkh*.c" -type f | sort -r | head -8 | sed 's/\.\\/test_//' | sed 's/\.c//'`)
#   cd ..
#   find build/gcov/out/ ! -name rkh$module*.gc* -type f | xargs sudo rm -f
done

cd ../../$ceedling_dir/gcov/
sudo lcov "${add[@]}" -o rkh-coverage.info
sudo genhtml rkh-coverage.info -o .

exit 0

