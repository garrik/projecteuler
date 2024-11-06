cmake_minimum_required(VERSION 3.28.0)
# At least add the `C` language option
project("Euler problem 3" C)

add_executable(main main.c primes.c util.c)

# Build with the highest severity possible
target_compile_options(main PRIVATE -Wall -Werror -Wextra -pedantic)

# Link to math library libm
# The linker presumes all libraries to begin with lib, 
# so to link to libm you link to m
target_link_libraries(main m)
