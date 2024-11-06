#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>

#include "../primes.h"

// the following variables are used for caclulations in primes.c
size_t primes_length = 10;
long int primes[10] = {0};
long int primes_count = 0;

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

static void test_first_primes(void **state) {
    (void) state; /* unused */
    assert_true(is_prime(2));
    assert_true(is_prime(3));
    assert_true(is_prime(5));
    assert_true(is_prime(7));
    assert_true(is_prime(11));
    assert_true(is_prime(13));
    assert_true(is_prime(17));
    assert_true(is_prime(19));
    assert_true(is_prime(23));
    assert_true(is_prime(29));
}

static void test_first_not_primes(void **state) {
    (void) state; /* unused */
    assert_false(is_prime(0));
    assert_false(is_prime(1));
    assert_false(is_prime(4));
    assert_false(is_prime(6));
    assert_false(is_prime(8));
    assert_false(is_prime(10));
    assert_false(is_prime(12));
    assert_false(is_prime(14));
    assert_false(is_prime(15));
    assert_false(is_prime(16));
    assert_false(is_prime(18));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_first_primes),
        cmocka_unit_test(test_first_not_primes)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}