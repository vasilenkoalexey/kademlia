#!/bin/sh

set -e

binary_dir=$(pwd)
source_dir=$(cd $(dirname $0)/..; pwd)

CXXFLAGS="-fprofile-arcs -ftest-coverage" cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
lcov --quiet --output-file app_base.info --initial --capture --directory .
cmake --build . -- -j $(sysctl -n hw.ncpu)
cmake --build . --target test -- -j $(sysctl -n hw.ncpu)
lcov --quiet --output-file app_test.info --capture --directory .
lcov --quiet --output-file app_total.info --add-tracefile app_base.info --add-tracefile app_test.info
lcov --quiet --output-file app_total_stripped.info --extract app_total.info "*/include/kademlia/*" "*/src/kademlia/*"
genhtml --output-directory html --num-spaces 4 --title "Kademlia unit tests" --demangle-cpp --no-function-coverage --prefix ${source_dir} app_total_stripped.info
