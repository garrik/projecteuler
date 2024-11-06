#include <stdio.h>
#include <stdbool.h>

#include "primes.h"

#define TARGET 600851475143 // number of which we want the largest prime factor
#define SIZE 1000 // maximum quantity of primes we can consider

// the following variables are used for caclulations in primes.c
size_t primes_length = SIZE;
long int primes[SIZE] = {0};
long int primes_count = 0;

long int dividers[SIZE] = {0};
size_t dividers_count = 0;
void add_to_dividers(long int n)
{
    // todo: increase array size when it is not big enough
    dividers[dividers_count++] = n;
}

int main()
{
    unsigned long int target = TARGET;
    long int quotient = target;
    long int max_divider = 0;

    printf("Look for the largest prime factor of the number %lu\n", target);
    // quoziente = target
    for (unsigned long int i = 0; i < target; i++) {
        // i e' l'indice dell'array di n primi
        // recupero n primo da $primi (se necessario calcolo il next n primo)
        long int prime = get_next_prime(i);
        if (prime == NOT_PRIME_NUM) {
            printf("cannot get next prime, bye!\n");
            return 1;
        }
        // quoziente % n == 0?
        // se resto 0: quoziente = quoziente / n, i = 0, aggiungo n nei divisori di target
        // se resto non 0: proseguo ciclo
        if (quotient % prime == 0) {
            quotient = quotient / prime;
            i = 0;
            add_to_dividers(prime);
            printf("new divider found %ld, new quotient %ld\n", prime, quotient);
        }
        // se quoziente == 1 fine
        if (quotient == 1) {
            break;
        }
    }

    for (size_t i = 0; i < dividers_count; i++) {
        if (max_divider < dividers[i]) {
            max_divider = dividers[i];
        }
    }

    printf("The largest prime factor of the number %ld is %ld\n", target, max_divider);
    return 0;
}