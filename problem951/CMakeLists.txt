cmake_minimum_required(VERSION 3.28.0)
# At least add the `C` language option
project("Euler problem 951" C)

add_executable(main
    main.c
    problem951.c
    problem951.h
)

# Build with the highest severity possible
target_compile_options(main PRIVATE -Wall -Werror -Wextra -pedantic)
