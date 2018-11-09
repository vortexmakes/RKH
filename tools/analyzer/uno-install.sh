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

cd ~
# Download
wget http://www.spinroot.com/uno/uno_v214.tar.gz

# Extract
tar xvf uno_v214.tar.gz

# Build
cd uno/src
cf='-DPC -ansi -Wall -ggdb -DCPP="\\"gcc -E\\"" -DBINDIR=\\"$(BINDIR)\\"'
sed -i "s/^CFLAGS=.*/CFLAGS=${cf}/" makefile
make

# Install
sudo make install

# Test
uno -V | grep -q "Version 2.14"

exit $?

