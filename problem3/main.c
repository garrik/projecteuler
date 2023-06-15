#include <stdio.h>
#include <stdbool.h>

#define TARGET 600851475143
#define NOT_PRIME_NUM 0
#define SIZE 1000

int is_prime(long int n)
{
    if (n == 0) {
        return false;
    }
    else if (n < 4) {
        return true;
    }
    else if (n % 2 == 0) {
        return false;
    }
    for (long int i = 3; i < n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

long int primes[SIZE] = {};
size_t primes_count = 0;
long int get_max_prime()
{
    return primes_count > 0 ? primes[primes_count - 1] : NOT_PRIME_NUM;
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
    primes[primes_count++] = n;
}

long int get_next_prime(int index)
{
    // printf("get next prime at %d\n", index);
    if (index >= SIZE) {
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

long int dividers[SIZE] = {};
size_t dividers_count = 0;
void add_to_dividers(long int n)
{
    // todo: increase array size when it is not big enough
    dividers[dividers_count++] = n;
}

int main(int argc, int **argv)
{
    long int target = TARGET;
    long int quotient = target;
    long int max_divider = 0;

    printf("Look for the largest prime factor of the number %ld\n", target);
    // quoziente = target
    for (long int i = 0; i < target; i++) {
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