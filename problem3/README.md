# Largest prime factor
## Problem 3
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143?

## Build
Math library needs to be linked using `-lm`, see `man sqrt`.
`gcc -Wall -Werror -Wextra -pedantic main.c primes.c util.c -lm -o main`

## Tests
`gcc -Wall -Werror -Wextra -pedantic test.c ../primes.c -o test -l cmocka -lm`