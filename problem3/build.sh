#!/bin/bash
# Build the project

# setup script to stop if any command fails and be verbose
set -ev

rm -rf ${HOME}/develop/build/projecteuler/problem3

cmake -S. -B${HOME}/develop/build/projecteuler/problem3
cd ${HOME}/develop/build/projecteuler/problem3
make -j`nproc`
