#!/bin/sh

#
# Arguments are:
#
# 1) A space spearated list of source files.
# 2) A space separated list of module source files.
# 3) The name of the executable to build.
#
# Environment variables used are:
#
# CXX - the name of the clang compiler, defaults to clang++.
# CXXFLAGS - flags to pass to the build, defaults to "-std=c++20 -g".
# LINKFLAGS - flags to pass to the link stage, defaults to "".
# LIBRARIES - Additional libraries to add to the end of the link command line, defaults to "".
#

: ${CXX:="clang++"}
: ${CXXFLAGS:="-std=c++20 -g"}

module_usage=""

for module_file in $2; do
module_base="${module_file%.*}"
$CXX $CXXFLAGS -x c++-module $module_file --precompile -o $module_base.pcm || exit 1

# grab the name of the exported module from the source:
cxx_module_name=$(grep -E "export[ ]+module[ ]+([^; ]+)" $module_file | sed -r "s/export[ ]+module[ ]+([^; ]+)[ ]*;/\1/")

# Build the command line for module usage:
module_usage="$module_usage -fmodule-file=$cxx_module_name=$module_base.pcm $module_base.pcm"

done

# Build the actual executable:
$CXX $CXXFLAGS $1 $module_usage $LIBRARIES -o $3 || exit 1
