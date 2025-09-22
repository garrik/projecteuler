#pragma once

#include <stdio.h>
#include <stdlib.h>

#define NODES_MAX_CAPACITY 1000

extern const int n; // # of red and black cards in the deck

typedef enum { black_card, red_card, none } card;
struct swap_positions {
    int r; // position of red card after swap [n, nn-1]
    int b; // position of black card after swap [0, 0 n-1]
};

int solve_problem_for_n();

unsigned long long factorial(unsigned long long n);

void create_sequences(const int sequence_count,
                      const int sequence_length,
                      card sequences[sequence_count][sequence_length]);

int update_swap_indexes(int ri[], int bi[], int swap_count, int sequence_length);

void swap_indexes_to_sequences(struct swap_positions **sp,
                               int *swap_positions_counts,
                               int sequence_count,
                               int sequence_length,
                               card sequences[sequence_count][sequence_length]);

void init_bi_ri(int bi[], int ri[], int length, int n);

void print_ri_bi(int ri[], int bi[], int length);

char t(card c);

void print_sequences(int sequence_count,
                     int sequence_length,
                     card sequences[sequence_count][sequence_length]);

void print_cards(card cards[],
                 int card_count);

typedef enum { player_one, player_two } player;
struct node {
    struct node *left;
    struct node *right;
    player player;
    card draw;
};

void create_games_tree(const card *sequence, const int sequence_card_count, const int sequence_card_index,
                       struct node *nodes, const int nodes_length, int *node_index,
                       struct node *prev_node, const player current_player, const int double_draw);

void print_games_tree(struct node *node, int depth);

void export_tree_to_dot_stdout(struct node *root);

void count_wins_per_player(const struct node *node,
                           const int depth,
                           const int max_depth,
                           int *player_one_wins, 
                           int *player_two_wins);

void calculate_sequences_fairness(int sequence_count,
                                  int sequence_length,
                                  card sequences[sequence_count][sequence_length],
                                  int sequences_fairness[]);

