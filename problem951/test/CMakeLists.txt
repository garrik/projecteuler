cmake_minimum_required(VERSION 3.28.0)
# At least add the `C` language option
project("Euler problem 951 test" C)

# Build the test
add_executable(test_problem
    test_factorial.c
    ../../unity/src/unity_internals.h
    ../../unity/src/unity.c
    ../../unity/src/unity.h
    ../problem951.c
    ../problem951.h
)

# Build with the highest severity possible
target_compile_options(test_problem PRIVATE -Wall)

# Enable CTest to run with `make test`
include(CTest)
add_test(NAME "Test Problem 951" COMMAND test_problem)