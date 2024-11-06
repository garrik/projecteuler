#include <stdbool.h>
#include <stdio.h>

#include "primes.h"

int is_prime(long int n){
    if (n < 2) {
        return false;
    }
    for (long int i = 2; i < n; i += 1) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

long int get_max_prime()
{
    return primes_length > 0 ? primes[primes_length - 1] : NOT_PRIME_NUM;
}

long int look_for_next_prime_from(long int begin)
{
    long int i;
    for (i = begin + 1; begin <= i; i += 1) {
        if (is_prime(i)) {
            printf("new prime found: %ld\n", i);
            return i;
        }
    }
    return NOT_PRIME_NUM;
}

void add_to_primes(long int n)
{
    // todo: increase array size when it is not big enough
    primes[primes_length++] = n;
}

long int get_next_prime(int index)
{
    // printf("get next prime at %d\n", index);
    if (index >= primes_length) {
        return NOT_PRIME_NUM; // primes array overflow
    }
    long int prime = primes[index];
    if (prime == NOT_PRIME_NUM) {
        long int max_prime = get_max_prime();
        prime = look_for_next_prime_from(max_prime);
        if (prime != NOT_PRIME_NUM) {
            add_to_primes(prime);
        }
    }
    return prime;
}