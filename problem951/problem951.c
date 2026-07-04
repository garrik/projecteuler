#include "fs_util.h"
#include "problem951.h"

// n is # of red and black cards in the deck
int solve_problem_for_n(const int n)
{
    const int sequence_length = n * 2; // number of cards in the deck
    // number of possible configurations of the cards in the deck
    const int total_sequence_count = factorial(2 * n) /
                                     (factorial(n) * factorial(n));

    printf("Number %d has %d total sequences\n", n, total_sequence_count);
    const int sequence_count = total_sequence_count / 2;
    card sequences[total_sequence_count][sequence_length];
    
    printf("Create %d sequences, half of possible configurations\n", sequence_count);
    create_sequences(total_sequence_count,
                     sequence_length,
                     sequences);
    printf("Sequences created\n");

    // print_sequences(sequence_count,
    //                 sequence_length,
    //                 sequences);
    save_sequences(n, sequence_count, sequence_length, sequences);

    int sequences_fairness[sequence_count];
    calculate_sequences_fairness(n,
                                 sequence_count,
                                 sequence_length,
                                 sequences,
                                 sequences_fairness);
    printf("Fairness of sequences calculated\n");

    int fairness = 0;
    for (int i = 0; i < sequence_count; i++) {
        fairness += sequences_fairness[i];
    }
    fairness *= 2;
    printf("F(%d) = %d\n", n, fairness);

    return 0;
}

unsigned long long factorial(unsigned long long n)
{
    if (n == 0) return 1;
    unsigned long long f = 1;
    while(n > 1) {
        f *= n;
        n -= 1;
    }
    return f;
}

// Create half of total possible sequences
// since the other half are symmetric with inverted colors
void create_sequences(const int sequence_count,
                      const int sequence_length,
                      card sequences[sequence_count][sequence_length])
{
    struct swap_positions **sp;
    sp = malloc(sequence_count * sizeof(struct swap_positions *));
    int *swap_positions_counts = malloc(sequence_count * sizeof(int));
    sp[0] = malloc(sizeof(struct swap_positions));
    sp[0][0] = (struct swap_positions){ .r = -1, .b = -1 };
    const int n = sequence_length / 2;
    const int max_swap_count = n > 2 ? n - 2 : 1;
    int bi[max_swap_count];
    int ri[max_swap_count];
    int swap_count = 1;
    int increase_swap_count_flag = 0;
    // init 1st sequence for given swap_count
    init_bi_ri(bi, ri, swap_count, n);
    // create sequences of index to swap cards for a
    for(int i = 1; i < sequence_count; i++) {
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
        
        if(update_swap_indexes(sequence_length, swap_count, ri, bi) == 1){
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
    for(int i = 1; i < sequence_count; i++) {
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
    
    swap_indexes_to_sequences(sequence_count,
                              sequence_length,
                              sequences,
                              sp,
                              swap_positions_counts);
    
    for (int i = 0; i < sequence_count; i++) {
        free(sp[i]);
    }
    free(sp);
    free(swap_positions_counts);
}

// init array of index of cards to swap for both colors
// e.g.
// n = 2, swap_count = 1 RRBB     -> bi[0] = 0, ri[0] = 2 -> swap R@0 with B@2 -> BRRB
// n = 3, swap_count = 1 RRRBBB   -> bi[0] = 0, ri[0] = 3 -> swap R@0 with B@3 -> BRRRBB
// n = 4, swap_count = 1 RRRRBBBB -> bi[0] = 0, ri[0] = 4 -> swap R@0 with B@4 -> BRRRRBBB
// n = 4, swap_count = 2 RRRRBBBB -> bi[0] = 0, bi[1] = 1, ri[0] = 4, ri[1] = 5 -> swap R@0 with B@4 -> BRRRRBBB
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
int update_swap_indexes(const int sequence_length, 
                        const int swap_count, 
                        int ri[], 
                        int bi[])
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
    const int n = sequence_length / 2;
    int k = swap_count - 1, d = 0, max = 0;
    //printf("    ri k@max");
    while(k >= 0) {
        max = sequence_length - 1 - d;
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

void swap_indexes_to_sequences(const int sequence_count,
                               const int sequence_length,
                               card sequences[sequence_count][sequence_length],
                               struct swap_positions **sp,
                               int *swap_positions_counts)
{
    const int n = sequence_length / 2;
    for(int i = 0; i < sequence_count; i++) {
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
        for(int j = n; j < sequence_length; j++){
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

void print_sequences(int sequence_count,
                     int sequence_length,
                     card sequences[sequence_count][sequence_length])
{
    printf("show sequences\n");
    for(int i = 0; i < sequence_count; i++) {
        printf("%d) ", i + 1);
        print_cards(sequences[i], sequence_length);
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

void calculate_sequences_fairness(const int n,
                                  int sequence_count,
                                  int sequence_length,
                                  card sequences[sequence_count][sequence_length],
                                  int sequences_fairness[])
{
    struct player_turn turns[TURNS_MAX];

    //print_cards(sequences[0], sequence_length);
    for (int i = 0; i < sequence_count; i++) {
        create_games_trees(sequence_length, sequences[i], TURNS_MAX, turns);

        // printf("\nTree structure:\n");
        // print_games_tree(&nodes[0], 0);
        // https://dreampuf.github.io/GraphvizOnline/
        save_tree_to_graphviz_dot_file(n, i, sequence_length, sequences[i], &turns[0]);

        int player_one_wins = 0, player_two_wins = 0;
        count_wins_per_player(&turns[0], 0, sequence_length - 1,
                              &player_one_wins, &player_two_wins);
        sequences_fairness[i] = player_one_wins == player_two_wins;
        printf("%d) Sequence ", i + 1);
        print_cards(sequences[i], sequence_length);
        printf(" is %s", sequences_fairness[i] ? "fair" : "unfair");
        printf(", player 1 wins: %d, player 2 wins: %d\n", player_one_wins, player_two_wins);
    }
}


// each sequence of cards generates multiple games 
// when there is a chance of double draw, two different games are possible
// each game is made of a unique sequence of turns
// the turns are identified by the player and the card drawn
void create_games_trees(const int sequence_length, const card sequence[sequence_length],
                        const int turns_length, struct player_turn turns[turns_length])
{
    int node_index = 0;
    int card_index = 0;
    struct player_turn* prev_node = NULL;
    // keep track of last turns for each game to complete all possible games
    struct player_turn* last_turns[TURNS_MAX] = { 0 };
    int last_turns_length = 1;
    while(card_index < sequence_length) {
        // current player draw
        const card draw = sequence[card_index];

        int next_last_turns_length = last_turns_length;
        for (int i = 0; i < last_turns_length; i++) {
            // select last turn of some game
            prev_node = last_turns[i];

            // set variables dependant on prev turn
            player current_player = prev_node == NULL ? player_one :
                                    prev_node->player == player_one ? player_two : player_one;
            bool prev_double_draw = prev_node == NULL ? false : prev_node->is_double_draw;
            bool is_double_draw;

            // detect double draw possibility
            if (prev_node && !prev_double_draw) {
                if (prev_node->draw == draw) {
                    is_double_draw = true;
                }
                else {
                    is_double_draw = false;
                }
            }
            else {
                is_double_draw = false;
            }

            // init game tree double draw node (right branch)
            if (is_double_draw) {
                struct player_turn *current_node = &turns[node_index];
                current_node->left = NULL;
                current_node->right = NULL;
                current_node->draw = draw; // equal to prev
                current_node->player = prev_node->player;
                current_node->is_double_draw = true;
                // go to next node
                node_index++;

                // double draws follow the right branch
                if (prev_node) {
                    prev_node->right = current_node;
                }

                // a new game sequence starts, keep track of last turn
                last_turns[next_last_turns_length] = current_node;
                next_last_turns_length++;
            }

            // init game tree regular node (left branch)
            struct player_turn *current_node = &turns[node_index];
            current_node->left = NULL;
            current_node->right = NULL;
            current_node->draw = draw;
            current_node->player = current_player;
            current_node->is_double_draw = false;
            // go to next node
            node_index++;

            // regular draws follow the left branch
            if (prev_node) {
                prev_node->left = current_node;
            }

            last_turns[i] = current_node;
        }

        last_turns_length = next_last_turns_length;
        card_index++;
    }
}

void print_games_tree(struct player_turn *node, int depth)
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

void count_wins_per_player(const struct player_turn* turn,
                           const int depth,
                           const int max_depth,
                           int* player_one_wins,
                           int* player_two_wins)
{
    if (turn == NULL) {
        return;
    }

    if (depth == max_depth) {
        if (turn->player == player_one) {
            (*player_one_wins)++;
        }
        else {
            (*player_two_wins)++;
        }
    }

    count_wins_per_player(turn->left, depth + 1, max_depth,
                          player_one_wins, player_two_wins);
    count_wins_per_player(turn->right, depth + 1, max_depth,
                          player_one_wins, player_two_wins);
}

void export_tree_to_dot_stdout(struct player_turn *root)
{
    if (root == NULL) return;

    printf("digraph GameTree {\n");
    printf("  node [shape=ellipse, style=filled, fillcolor=lightgray];\n");

    // BFS
    struct player_turn *queue[TURNS_MAX];
    int ids[TURNS_MAX];  // node ID
    int front = 0, rear = 0;

    queue[rear] = root;
    ids[rear] = 0;
    rear++;

    int current_id = 1; // next available ID

    while (front < rear) {
        struct player_turn *curr = queue[front];
        int curr_id = ids[front];
        front++;

        // Label for this node
        printf("  node%d [label=\"Player %d drew %c\"];\n",
               curr_id,
               curr->player == player_one ? 1 : 2,
               t(curr->draw));

        // Left child
        if (curr->left && rear < TURNS_MAX) {
            int left_id = current_id++;
            printf("  node%d -> node%d [label=\"L\"];\n", curr_id, left_id);

            queue[rear] = curr->left;
            ids[rear] = left_id;
            rear++;
        }

        // Right child
        if (curr->right && rear < TURNS_MAX) {
            int right_id = current_id++;
            printf("  node%d -> node%d [label=\"R\"];\n", curr_id, right_id);

            queue[rear] = curr->right;
            ids[rear] = right_id;
            rear++;
        }
    }

    printf("}\n");
}
