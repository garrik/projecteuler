# Largest prime factor
## Problem 3
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143?

## Manual build
Math library needs to be linked using `-lm`, see `man sqrt`.
`gcc -Wall -Werror -Wextra -pedantic main.c primes.c util.c -lm -o main`

## Manual build of test
`gcc -Wall -Werror -Wextra -pedantic test.c ../primes.c -o test -l cmocka -lm`

## CMake build
Setup an out of tree build with cmake
```bash
cmake -S. -B${HOME}/develop/build/projecteuler/problem3
cd ${HOME}/develop/build/projecteuler/problem3
make -j`nproc`
```

or use `build.sh`

Setup out of tree build for test
```bash
cd test
cmake -S. -B${HOME}/develop/build/projecteuler/problem3_test
cd ${HOME}/develop/build/projecteuler/problem3_test
make
```