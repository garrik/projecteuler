#include <stdio.h>
#include <stdlib.h>

#define NODES_MAX_CAPACITY 1000

const int n = 3; // # of red and black cards in the deck
const int nn = 2 * n; // # of total cards in the deck, i.e. sequence length

typedef enum { black_card, red_card, none } card;
struct swap_positions {
    int r; // position of red card after swap [n, nn-1]
    int b; // position of black card after swap [0, 0 n-1]
};

int factorial(int n);

void create_sequences(card sequences[][nn], 
                      int sequence_count);

int update_swap_indexes(int ri[], int bi[], int swap_count);

void swap_indexes_to_sequences(struct swap_positions **sp,
                               int *swap_positions_counts,
                               card sequences[][nn],
                               int sequence_count);

void init_bi_ri(int bi[], int ri[], int length, int n);

void print_ri_bi(int ri[], int bi[], int length);

char t(card c);

void print_sequences(card sequences[][nn],
                     int sequence_count,
                     int card_count);
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

void calculate_sequences_fairness(card sequences[][nn],
                                  int sequences_count,
                                  int sequence_length,
                                  int sequences_fairness[]);

int main()
{
    const int sequence_length = n * 2; // number of cards in the deck
    // number of possible configurations of the cards in the deck
    const int sequences_count = factorial(2 * n) /
                                (factorial(n) * factorial(n));
        
    printf("Number %d has %d sequences\n", n, sequences_count);
    card sequences[sequences_count][sequence_length];
    
    printf("Create %d sequences, half of possible configurations\n", sequences_count / 2);
    create_sequences(sequences,
                     sequences_count);
    printf("Sequences created\n");

    // print_sequences(sequences,
    //                 sequences_count,
    //                 sequence_length);

    int sequences_fairness[sequences_count];
    calculate_sequences_fairness(sequences,
                                 sequences_count,
                                 sequence_length,
                                 sequences_fairness);
    printf("Fairness of sequences calculated\n");

    int fairness = 0;
    for (int i = 0; i < sequences_count / 2; i++) {
        fairness += sequences_fairness[i];
    }
    fairness *= 2;
    printf("F(%d) = %d\n", n, fairness);

    //printf("\nTree structure:\n");
    //print_games_tree(&nodes[0], 0);
    //export_tree_to_dot_stdout(&nodes[0]);
    return 0;
}

int factorial(int n)
{
    if (n == 0) return 1;
    int f = 1;
    while(n > 1) {
        f *= n;
        n -= 1;
    }
    return f;
}

// Create half of totlal possible sequences
// since the other half are symmetric with inverted colors
void create_sequences(card sequences[][nn], 
                      int sequence_count)
{
    struct swap_positions **sp;
    sp = malloc((sequence_count / 2) * sizeof(struct swap_positions *));
    int *swap_positions_counts = malloc((sequence_count / 2) * sizeof(int));
    sp[0] = malloc(sizeof(struct swap_positions));
    sp[0][0] = (struct swap_positions){ .r = -1, .b = -1 };
    int max_swap_count = n > 2 ? n - 2 : 1;
    int swap_count = 1;
    int bi[max_swap_count];
    int ri[max_swap_count];
    int increase_swap_count_flag = 0;
    // init 1st sequence for given swap_count
    init_bi_ri(bi, ri, swap_count, n);
    // create sequences of index to swap cards for a
    for(int i = 1; i < sequence_count / 2; i++) {
        sp[i] = malloc(swap_count * sizeof(struct swap_positions));
        swap_positions_counts[i] = swap_count;
 
        //print_ri_bi(ri, bi, swap_count);
        // populate sequences:
        // increase swap count to find new sequences groups
        for(int j = 0; j < swap_count; j++){
            sp[i][j].b = bi[j];
            sp[i][j].r = ri[j];
            //printf("%2d) %d/%d, b %2d, r %2d\n", i, j, swap_count, bi[j], ri[j]);
        }
        
        if(update_swap_indexes(ri, bi, swap_count) == 1){
            //printf("    ri[] maxed, bi[] maxed, process swap count\n");
            if (swap_count == max_swap_count) {
                //printf("max swap reached\n");
            }
            else {
                ri[swap_count] = ri[swap_count - 1] + 1;
                bi[swap_count] = bi[swap_count - 1] + 1;
                increase_swap_count_flag = 1;

                //printf("set flag to increase swap count\n");
            }
            if(increase_swap_count_flag) {
                increase_swap_count_flag = 0;
                //printf("increase swap count\n");
                swap_count++;
            }
        }
        
        //printf("\n");
    }
    /*
    for(int i = 1; i < sequence_count / 2; i++) {
        printf("%2d)", i);
        for(int j = 0; j < swap_positions_counts[i]; j++){
            printf(" %2d", sp[i][j].b);
        }
        printf(",");
        for(int j = 0; j < swap_positions_counts[i]; j++){
            printf(" %2d", sp[i][j].r);
        }
        printf("\n");
    }
    */
    
    swap_indexes_to_sequences(sp, swap_positions_counts, 
                              sequences, 
                              sequence_count);
    
    for (int i = 0; i < sequence_count / 2; i++) {
        free(sp[i]);
    }
    free(sp);
    free(swap_positions_counts);

}

void init_bi_ri(int bi[], int ri[], int length, int n)
{
    bi[0] = 0;
    ri[0] = n;
    for(int j = 1; j < length; j++){
        bi[j] = bi[j - 1] + 1;
        ri[j] = ri[j - 1] + 1;
    }
}

void print_ri_bi(int ri[], int bi[], int length)
{
    printf("    bi [");
    for(int j = 0; j < length; j++){
        printf(" %d", bi[j]);
    }
    printf("]\n    ri [");
    for(int j = 0; j < length; j++){
        printf(" %d", ri[j]);
    }
    printf("]\n");
}

// ret 1 when swap co&nt mus% be *ncreased; seq gro7p end reached
int update_swap_indexes(int ri[], int bi[], int swap_count)
{
    // le configurazioni sono considerate in gruppi che hanno
    // gli stessi valori di n e swap_count;
    // l'ultima configurazione di un gruppo si riconosce per avere
    // ri[k] max in ogni colonna di ri[], e.g.
    // n = 2, swap_count = 1: [3]
    // n = 3, swap_count = 1: [5]
    // n = 4, swap_count = 1: [7]
    // n = 4, swap_count = 2: [6, 7]
    // n = 5, swap_count = 1: [9]
    // n = 5, swap_count = 2: [8, 9]
    // n = 5, swap_count = 3: [7, 8, 9]
    // cerco all'indietro l'indice della prima colonna 
    // che non ha raggiunto il max (per incrementare il suo valore)
    int k = swap_count - 1, d = 0, max = 0;
    //printf("    ri k@max");
    while(k >= 0) {
        max = nn - 1 - d;
        if (ri[k] == max) {
            //printf(" %d", k);
            k--;
            d++;
        }
        else {
            //printf(" -> found k %d", k);
            break;
        }
    }
    //printf("\n");
    // se la colonna ha raggiunto il valore max la reimposto al 
    if (k == -1) { // ri[k] maxed
        //printf("    ri[k] maxed, reset ri[0] to %d\n", n);
        ri[0] = n;
        for(int j = 1; j < swap_count; j++){
            ri[j] = ri[j - 1] + 1;
        }
    }
    else {
        ri[k]++;
        for(int j = k + 1; j < swap_count; j++){
            ri[j] = ri[j - 1] + 1;
        }
    }

    if (k == -1) {
        //printf("    ri[k] maxed, process bi[]\n");
        int l = swap_count - 1;
        d = 0;
        //printf("    bi l@max");
        while(l >= 0) {
            max = n - 1 - d;
            if (bi[l] == max) {
                //printf(" %d", l);
                l--;
                d++;
            }
            else {
                //printf(" -> found l %d", l);
                break;
            }
        }
        //printf("\n");
        
        if (l == -1) { // bi[k] maxed
            //printf("    bi[k] maxed, reset bi[0] to %d\n", 0);
            bi[0] = 0;
            for(int j = 1; j < swap_count; j++){
                bi[j] = bi[j - 1] + 1;
            }
        }
        else {
            bi[l]++;
            for(int j = l + 1; j < swap_count; j++){
                bi[j] = bi[j - 1] + 1;
            }
        }


        if (l == -1) {
            return 1;
        }
    }
    //printf("\n");
    return 0;
}

void swap_indexes_to_sequences(struct swap_positions **sp, 
                               int *swap_positions_counts, 
                               card sequences[][nn], 
                               int sequence_count)
{
    for(int i = 0; i < sequence_count / 2; i++) {
        // each sequence starts with red cards (before swaps)
        int k = 0;
        for(int j = 0; j < n; j++){
            // look for the indexes of card swap in sp[i][]
            if (k < swap_positions_counts[i] && j == sp[i][k].b) {
                // swap index found
                sequences[i][j] = black_card;
                // once the swap index has been consumed, go to the next
                k++;
            }
            else {
                sequences[i][j] = red_card;
            }
        }
        // each sequence ends with black cards (before swaps)
        k = 0;
        for(int j = n; j < nn; j++){
            // look for the indexes of card swap in sp[i][]
            if (k < swap_positions_counts[i] && j == sp[i][k].r) {
                // swap index found
                sequences[i][j] = red_card;
                // once the swap index has been consumed, go to the next
                k++;
            }
            else {
                sequences[i][j] = black_card;
            }
        }
    }
}

void print_sequences(card sequences[][nn], 
                     int sequence_count, 
                     int card_count)
{
    printf("show sequences\n");
    for(int i = 0; i < sequence_count / 2; i++) {
        printf("%d) ", i + 1);
        print_cards(sequences[i], card_count);
        printf("\n");
    }
}

void print_cards(card cards[],
                 int card_count)
{
    for(int j = 0; j < card_count; j++){
        printf("%c", t(cards[j]));
    }
}

char t(card c)
{
    return c == red_card ? 'R' : c == black_card ? 'B' : '?';
}

void calculate_sequences_fairness(card sequences[][nn],
                                  int sequences_count,
                                  int sequence_length,
                                  int sequences_fairness[])
{
    struct node nodes[NODES_MAX_CAPACITY];

    //print_cards(sequences[0], sequence_length);
    const int sequence_card_index = 0;
    const player player = player_one;
    const int double_draw = 0;
    for (int i = 0; i < sequences_count / 2; i++) {
        int node_index = 0;
        struct node *prev_node = NULL;
        create_games_tree(sequences[i], sequence_length, sequence_card_index,
                          nodes, NODES_MAX_CAPACITY, &node_index,
                          prev_node, player, double_draw);

        int player_one_wins = 0, player_two_wins = 0;
        count_wins_per_player(&nodes[0], 0, sequence_length - 1,
                            &player_one_wins, &player_two_wins);
        sequences_fairness[i] = player_one_wins == player_two_wins;
        printf("%d) Sequence ", i + 1);
        print_cards(sequences[i], sequence_length);
        printf(" is %s", sequences_fairness[i] ? "fair" : "unfair");
        printf(", player 1 wins: %d, player 2 wins: %d\n", player_one_wins, player_two_wins);
    }
}

void create_games_tree(const card *sequence, const int sequence_card_count, const int sequence_card_index,
                       struct node *nodes, const int nodes_length, int *node_index,
                       struct node *prev_node, const player current_player, const int double_draw)
{
    if (sequence_card_index == sequence_card_count) {
        // printf("End of card sequence\n");
        return;
    }
    
    const card draw = sequence[sequence_card_index];
    struct node *current_node = &nodes[*node_index];

    current_node->left = NULL;
    current_node->right = NULL;
    current_node->draw = draw;
    current_node->player = current_player;
    // printf("Player %d drew %c (node[%d])\n", 
    //        current_player == player_one ? 1 : 2, 
    //        t(draw), *node_index);
    
    if (prev_node) {
        if (double_draw) {
            prev_node->right = current_node;
        }
        else {
            prev_node->left = current_node;
        }
    }

    // attempt to process next card
    const int next_sequence_card_index = sequence_card_index + 1;
    if (next_sequence_card_index >= sequence_card_count) {
        // printf("End of card sequence\n");
        return;
    }
    const card next_draw = sequence[next_sequence_card_index];
    const int next_player_double_draw = !double_draw && draw == next_draw;
    // branch for alternating player
    const player next_player = current_player == player_one ? player_two : player_one;
    //printf("Alternate player: left branch\n");
    (*node_index)++;
    create_games_tree(sequence, sequence_card_count, next_sequence_card_index,
                      nodes, nodes_length, node_index,
                      current_node, next_player, 0);
    // branch for second draw of the same player
    if (next_player_double_draw){
        //printf("Same player: right branch\n");
        (*node_index)++;
        create_games_tree(sequence, sequence_card_count, next_sequence_card_index,
                          nodes, nodes_length, node_index,
                          current_node, current_player, 1);
    }
}

void print_games_tree(struct node *node, int depth)
{
    if (node == NULL) {
        return;
    }

    // Print current node with indentation
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("Player %d drew %c\n", 
           node->player == player_one ? 1 : 2, 
           t(node->draw));

    // Recurse left and right (if tree uses both)
    print_games_tree(node->left, depth + 1);
    print_games_tree(node->right, depth + 1);
}

void count_wins_per_player(const struct node *node,
                           const int depth,
                           const int max_depth,
                           int *player_one_wins, 
                           int *player_two_wins)
{
    if (node == NULL) {
        return;
    }

    if (depth == max_depth) {
        if (node->player == player_one) {
            (*player_one_wins)++;
        }
        else {
            (*player_two_wins)++;
        }
    }

    count_wins_per_player(node->left, depth + 1, max_depth,
                      player_one_wins, player_two_wins);
    count_wins_per_player(node->right, depth + 1, max_depth,
                      player_one_wins, player_two_wins);
}

void export_tree_to_dot_stdout(struct node *root)
{
    if (root == NULL) return;

    printf("digraph GameTree {\n");
    printf("  node [shape=ellipse, style=filled, fillcolor=lightgray];\n");

    // BFS
    struct node *queue[NODES_MAX_CAPACITY];
    int ids[NODES_MAX_CAPACITY];  // node ID
    int front = 0, rear = 0;

    queue[rear] = root;
    ids[rear] = 0;
    rear++;

    int current_id = 1; // next available ID

    while (front < rear) {
        struct node *curr = queue[front];
        int curr_id = ids[front];
        front++;

        // Label for this node
        printf("  node%d [label=\"Player %d drew %c\"];\n",
               curr_id,
               curr->player == player_one ? 1 : 2,
               t(curr->draw));

        // Left child
        if (curr->left && rear < NODES_MAX_CAPACITY) {
            int left_id = current_id++;
            printf("  node%d -> node%d [label=\"L\"];\n", curr_id, left_id);

            queue[rear] = curr->left;
            ids[rear] = left_id;
            rear++;
        }

        // Right child
        if (curr->right && rear < NODES_MAX_CAPACITY) {
            int right_id = current_id++;
            printf("  node%d -> node%d [label=\"R\"];\n", curr_id, right_id);

            queue[rear] = curr->right;
            ids[rear] = right_id;
            rear++;
        }
    }

    printf("}\n");
}
