#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../palindrome.c"

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

static void test_palindromes(void **state) {
    (void) state; /* unused */
    assert_true(is_palindrome(0));
    assert_true(is_palindrome(01));
    assert_true(is_palindrome(11));
    assert_true(is_palindrome(101));
    assert_true(is_palindrome(1221));
    assert_true(is_palindrome(32123));
}

static void test_not_palindromes(void **state) {
    (void) state; /* unused */
    assert_false(is_palindrome(10));
    assert_false(is_palindrome(100));
    assert_false(is_palindrome(321));
    assert_false(is_palindrome(3224));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_palindromes),
        cmocka_unit_test(test_not_palindromes)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}