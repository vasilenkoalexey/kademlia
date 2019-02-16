#!/bin/sh

set -e

binary_dir=$(pwd)
source_dir=$(cd $(dirname $0)/..; pwd)
test_dir=test/unit_tests

CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ${source_dir}
cmake --build . -- -j $(sysctl -n hw.ncpu)
cmake --build . --target test -- -j $(sysctl -n hw.ncpu) 
xcrun llvm-profdata merge -output default.prof ${test_dir}/default.profraw
cd $source_dir
xcrun llvm-cov show \
    -instr-profile ${binary_dir}/default.prof \
    -Xdemangler xcrun -Xdemangler c++filt \
    -format html \
    -show-line-counts-or-regions \
    -output-dir $binary_dir/html \
    $binary_dir/$test_dir/kademlia-test \
    $(find src/kademlia include/kademlia -name '*.cpp' -or -name '*.hpp')
