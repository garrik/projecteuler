#include "../../unity/src/unity.h"
#include "../problem951.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_create_games_tree_n_2(void) {
    card sequences[3][4] = { // n = 2
        {red_card, red_card, black_card, black_card},
        {black_card, red_card, red_card, black_card},
        {black_card, red_card, black_card, red_card}
    };
    //int sequence_count = 3;
    int sequence_length = 4;

    struct node nodes[NODES_MAX_CAPACITY];

    const int sequence_index = 0;
    const player player = player_one;
    const int double_draw = 0;

    // Game tree: 0
    int node_index = 0;
    struct node *prev_node = NULL;
    int i = 0;
    create_games_trees(sequence_length, sequences[i], sequence_index,
                       NODES_MAX_CAPACITY, nodes, &node_index,
                       prev_node, player, double_draw);

    // Player 1 drew R - node 0
    TEST_ASSERT_EQUAL(sequences[i][0], nodes[0].draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].player);

    // Player 2 drew R - node 1
    // left branch: coin lands tail and 2nd player draws
    TEST_ASSERT_EQUAL(sequences[i][1], nodes[0].left->draw);
    TEST_ASSERT_EQUAL(player_two, nodes[0].left->player);

    // Player 1 drew R - node 2
    // right branch: coin lands head and 1st player draws again
    TEST_ASSERT_EQUAL(sequences[i][1], nodes[0].right->draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].right->player);

    // Player 1 drew B - node 3
    // left branch: coin lands tail and 2nd player draws
    TEST_ASSERT_EQUAL(sequences[i][2], nodes[0].left->left->draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].left->left->player);

    // Player 2 drew B - node 4
    TEST_ASSERT_EQUAL(sequences[i][2], nodes[0].right->left->draw);
    TEST_ASSERT_EQUAL(player_two, nodes[0].right->left->player);

    // Player 2 drew B - node 5
    TEST_ASSERT_EQUAL(sequences[i][3], nodes[0].left->left->left->draw);
    TEST_ASSERT_EQUAL(player_two, nodes[0].left->left->left->player);

    // Player 1 drew B - node 6
    TEST_ASSERT_EQUAL(sequences[i][3], nodes[0].left->left->right->draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].left->left->right->player);

    // Player 1 drew B - node 7
    TEST_ASSERT_EQUAL(sequences[i][3], nodes[0].right->left->left->draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].right->left->left->player);

    // Player 2 drew B - node 8
    TEST_ASSERT_EQUAL(sequences[i][3], nodes[0].right->left->right->draw);
    TEST_ASSERT_EQUAL(player_two, nodes[0].right->left->right->player);

    // Game tree: 1
    node_index = 0;
    prev_node = NULL;
    i = 1;
    create_games_trees(sequence_length, sequences[i], sequence_index,
                       NODES_MAX_CAPACITY, nodes, &node_index,
                       prev_node, player, double_draw);

    // Player 1 drew B - node 0
    TEST_ASSERT_EQUAL(sequences[i][0], nodes[0].draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].player);

    // Player 2 drew R - node 1
    TEST_ASSERT_EQUAL(sequences[i][1], nodes[0].left->draw);
    TEST_ASSERT_EQUAL(player_two, nodes[0].left->player);

    // Player 1 drew R - node 2
    TEST_ASSERT_EQUAL(sequences[i][2], nodes[0].left->left->draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].left->left->player);

    // Player 1 drew R - node 3
    TEST_ASSERT_EQUAL(sequences[i][2], nodes[0].left->right->draw);
    TEST_ASSERT_EQUAL(player_two, nodes[0].left->right->player);

    // Player 2 drew B - node 4
    TEST_ASSERT_EQUAL(sequences[i][3], nodes[0].left->left->left->draw);
    TEST_ASSERT_EQUAL(player_two, nodes[0].left->left->left->player);

    // Player 1 drew B - node 5
    TEST_ASSERT_EQUAL(sequences[i][3], nodes[0].left->right->left->draw);
    TEST_ASSERT_EQUAL(player_one, nodes[0].left->right->left->player);

}


// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_create_games_tree_n_2);
    return UNITY_END();
}

