#include <stdbool.h>
#include <stdio.h>

#define NOT_PRIME_NUM 0

extern size_t primes_length; // maximum quantity of primes we can store
extern long int primes[]; // array of found primes
extern long int primes_count; // current quantity of primes found

long int get_max_prime();

int is_prime(long int n);

long int look_for_next_prime_from(long int begin);

void add_to_primes(long int n);

long int get_next_prime(int index);