#include "../../unity/src/unity.h"
#include "../problem951.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_calc_factorials(void) {
    TEST_ASSERT_EQUAL(1      , factorial(0));
    TEST_ASSERT_EQUAL(1      , factorial(1));
    TEST_ASSERT_EQUAL(6      , factorial(3));
    TEST_ASSERT_EQUAL(24     , factorial(4));
    TEST_ASSERT_EQUAL(120    , factorial(5));
    TEST_ASSERT_EQUAL(3628800, factorial(10));
}

void test_init_bi_ri_for_n_2() {
    const int n = 2;
    const int max_swap_count = n > 2 ? n - 2 : 1;
    int bi[max_swap_count];
    int ri[max_swap_count];
    int expected_bi[] = { 0 };
    int expected_ri[] = { 2 };
    
    init_bi_ri(bi, ri, max_swap_count, n);

    TEST_ASSERT_EQUAL(expected_bi[0], bi[0]);
    TEST_ASSERT_EQUAL(expected_ri[0], ri[0]);
}

void test_init_bi_ri_for_n_3() {
    const int n = 3;
    const int max_swap_count = n > 2 ? n - 2 : 1;
    int bi[max_swap_count];
    int ri[max_swap_count];
    int expected_bi[] = { 0 };
    int expected_ri[] = { 3 };
    
    init_bi_ri(bi, ri, max_swap_count, n);

    TEST_ASSERT_EQUAL(expected_bi[0], bi[0]);
    TEST_ASSERT_EQUAL(expected_ri[0], ri[0]);
}

void test_init_bi_ri_for_n_4() {
    const int n = 4;
    const int max_swap_count = n > 2 ? n - 2 : 1;
    int bi[max_swap_count];
    int ri[max_swap_count];
    int expected_bi[] = { 0, 1 };
    int expected_ri[] = { 4, 5 };
    
    init_bi_ri(bi, ri, max_swap_count, n);

    TEST_ASSERT_EQUAL(expected_bi[0], bi[0]);
    TEST_ASSERT_EQUAL(expected_bi[1], bi[1]);
    TEST_ASSERT_EQUAL(expected_ri[0], ri[0]);
    TEST_ASSERT_EQUAL(expected_ri[1], ri[1]);
}

void test_init_bi_ri_for_n_5() {
    const int n = 5;
    const int max_swap_count = n > 2 ? n - 2 : 1;
    int bi[max_swap_count];
    int ri[max_swap_count];
    int expected_bi[] = { 0, 1, 2 };
    int expected_ri[] = { 5, 6, 7 };
    
    init_bi_ri(bi, ri, max_swap_count, n);

    TEST_ASSERT_EQUAL(expected_bi[0], bi[0]);
    TEST_ASSERT_EQUAL(expected_bi[1], bi[1]);
    TEST_ASSERT_EQUAL(expected_bi[2], bi[2]);
    TEST_ASSERT_EQUAL(expected_ri[0], ri[0]);
    TEST_ASSERT_EQUAL(expected_ri[1], ri[1]);
    TEST_ASSERT_EQUAL(expected_ri[2], ri[2]);
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
    create_sequences(sequence_count, sequence_length, sequences);

    for (int i = 0; i < sequence_count; i++) {
        for (int j = 0; j < sequence_length; j++) {
            TEST_ASSERT_EQUAL(sequences[i][j], sequences_expected[i][j]);
        }
    }
}

void test_create_sequences_for_n_3(void) {
    const int sequence_count = 10;
    const int sequence_length = 6;
    card sequences_expected[10][6] = {
        { red_card, red_card, red_card, black_card, black_card, black_card },
        { black_card, red_card, red_card, red_card, black_card, black_card },
        { black_card, red_card, red_card, black_card, red_card, black_card },
        { black_card, red_card, red_card, black_card, black_card, red_card },
        { red_card, black_card, red_card, red_card, black_card, black_card },
        { red_card, black_card, red_card, black_card, red_card, black_card },
        { red_card, black_card, red_card, black_card, black_card, red_card },
        { red_card, red_card, black_card, red_card, black_card, black_card },
        { red_card, red_card, black_card, black_card, red_card, black_card },
        { red_card, red_card, black_card, black_card, black_card, red_card }
    };

    card sequences[sequence_count][sequence_length];
    create_sequences(sequence_count, sequence_length, sequences);

    for (int i = 0; i < sequence_count; i++) {
        for (int j = 0; j < sequence_length; j++) {
            TEST_ASSERT_EQUAL(sequences_expected[i][j], sequences[i][j]);
        }
    }
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_calc_factorials);
    RUN_TEST(test_init_bi_ri_for_n_2);
    RUN_TEST(test_init_bi_ri_for_n_3);
    RUN_TEST(test_init_bi_ri_for_n_4);
    RUN_TEST(test_init_bi_ri_for_n_5);
    RUN_TEST(test_create_sequences_for_n_2);
    RUN_TEST(test_create_sequences_for_n_3);
    return UNITY_END();
}

