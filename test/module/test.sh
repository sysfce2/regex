#!/bin/sh

#
# Builds all of the tests in this folder using the supplied compiler-specific script in $1
#

for file in *.cpp; do

CXXFLAGS="-std=c++20 -g -I ../../../.." $1 $file ../../module/regex.cxx "${file%.*}.exe" || exit 1

done
