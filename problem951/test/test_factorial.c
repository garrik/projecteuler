#include "../../unity/src/unity.h"
#include "../problem951.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_calc_factorials(void) {
    TEST_ASSERT_EQUAL(factorial(0), 1);
    TEST_ASSERT_EQUAL(factorial(1), 1);
    TEST_ASSERT_EQUAL(factorial(3), 6);
    TEST_ASSERT_EQUAL(factorial(4), 24);
    TEST_ASSERT_EQUAL(factorial(5), 120);
    TEST_ASSERT_EQUAL(factorial(10), 3628800);
}

void test_create_sequences_for_n_2(void) {
    card sequences_expected[3][4] = {
        { red_card, red_card, black_card, black_card },
        { black_card, red_card, red_card, black_card },
        { black_card, red_card, black_card, red_card }
    };

    card sequences[3][4];
    create_sequences(sequences, 6);

    for (int i = 0; i < 3; i++) {
        TEST_ASSERT_EQUAL(sequences[i][0], sequences_expected[i][0]);
        TEST_ASSERT_EQUAL(sequences[i][1], sequences_expected[i][1]);
        TEST_ASSERT_EQUAL(sequences[i][2], sequences_expected[i][2]);
        TEST_ASSERT_EQUAL(sequences[i][3], sequences_expected[i][3]);
    }
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_calc_factorials);
    RUN_TEST(test_create_sequences_for_n_2);
    return UNITY_END();
}

