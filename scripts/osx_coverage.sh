#!/bin/sh

set -e

binary_dir=$(pwd)
source_dir=$(dirname $0)/..
test_dir=test/unit_tests

# Convert 
(
    cd $binary_dir/$test_dir
    xcrun llvm-profdata merge -output default.prof default.profraw
)

# Generate report
(
    cd $source_dir/$project_dir
    xcrun llvm-cov show \
        -instr-profile $binary_dir/$test_dir/default.prof \
        -Xdemangler xcrun -Xdemangler c++filt \
        -format html \
        -show-line-counts-or-regions \
        -output-dir $binary_dir/$test_dir/report \
        $binary_dir/$test_dir/kademlia-test \
        $(find src include -name '*.cpp' -or -name '*.hpp')
)
