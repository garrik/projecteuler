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
    const int sequence_count = 3;
    const int sequence_length = 4;
    card sequences_expected[3][4] = {
        { red_card, red_card, black_card, black_card },
        { black_card, red_card, red_card, black_card },
        { black_card, red_card, black_card, red_card }
    };

    card sequences[sequence_count][sequence_length];
    create_sequences(sequence_count * 2, sequence_length, sequences);

    for (int i = 0; i < sequence_count; i++) {
        for (int j = 0; j < sequence_length; j++) {
            TEST_ASSERT_EQUAL(sequences[i][j], sequences_expected[i][j]);
        }
    }
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_calc_factorials);
    RUN_TEST(test_create_sequences_for_n_2);
    return UNITY_END();
}

