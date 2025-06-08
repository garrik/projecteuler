#!/bin/bash
# Build the project

# setup script to stop if any command fails and be verbose
set -eu # -e: exit if any command fails, -u: exit if any variable is unset, -v

problem=$1

if [ -z "$problem" ]; then
    echo "Usage: $0 <problem>"
    echo "E.g. $0 problem5"
    echo "E.g. $0 problem5/test"
    exit 1
fi

build_dir=${HOME}/develop/build/projecteuler/${problem}

# clean up previous build
rm -rf ${build_dir}
# generate the build
cd ${problem}
cmake -S. -B${build_dir} -DCMAKE_BUILD_TYPE=Release
# build
cd ${build_dir}
make -j$(nproc)

if [ $? -eq 0 ]; then
    echo
    echo "✅ Build successful"
    echo
    if [ -d "test" ]; then
        echo "Found test directory, running tests..."
        ctest --test-dir test --output-on-failure
    else
        echo "No test directory found, skipping tests"
    fi
fi
