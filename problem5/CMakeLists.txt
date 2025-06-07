cmake_minimum_required(VERSION 3.28.0)
# At least add the `C` language option
project("Euler problem 5" C)

add_executable(main main.c)

# Build with the highest severity possible
target_compile_options(main PRIVATE -Wall -Werror -Wextra -pedantic)
