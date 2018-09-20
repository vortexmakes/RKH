#!/bin/bash -e
#
# This makefile requires an ANSI compatible C compiler bison and flex.
#

source_dir="../../source"
uno_dir="tools/analyzer"

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
# Download
# Extract
# Build
# Install

exit 0

