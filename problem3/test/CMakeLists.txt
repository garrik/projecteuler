cmake_minimum_required(VERSION 3.28.0)
# At least add the `C` language option
project("Euler problem 3 test" C)

# Build the test
add_executable(test_problem test.c ../primes.c)

# Build with the highest severity possible
target_compile_options(test_problem PRIVATE -Wall -Werror -Wextra -pedantic)

# Dependencies
find_package(cmocka 0.8.0 REQUIRED)

# Link to math library libm
# The linker presumes all libraries to begin with lib, 
# so to link to libm you link to m
target_link_libraries(test_problem m cmocka)

# Enable CTest to run with `make test`
include(CTest)
add_test(NAME "Test Problem 3" COMMAND test_problem)