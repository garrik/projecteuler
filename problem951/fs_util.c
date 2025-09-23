#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fs_util.h"

int save_sequences(const int n,
                   const int sequence_count,
                   const int sequence_length,
                   card sequences[sequence_count][sequence_length]) {
    char dirname[256];
    sprintf(dirname, "solution_for_n_%d", n);
    if (!directory_exists(dirname)) {
        printf("Directory '%s' doesn't exist. Creating...\n", dirname);
        if (create_directory(dirname) == 0) {
            printf("Directory created successfully\n");
            char filepath[512];
            sprintf(filepath, "%s/sequences.dat", dirname);
            FILE *file = fopen(filepath, "w");
            if (file != NULL) {
                printf("File '%s' created successfully\n", filepath);
                for (int i = 0; i < sequence_count; i++) {
                    for (int j = 0; j < sequence_length; j++) {
                        fprintf(file, "%c", t(sequences[i][j]));
                    }
                    fprintf(file, "\n");
                }
                fclose(file);
                printf("Sequence file saved to disk\n");
            }
            else {
                perror("Failed to create file");
                printf("Sequence file not saved to disk\n");
                return 1;
            }
        } 
        else {
            perror("Failed to create directory");
            printf("Sequence file not saved to disk\n");
            return 1;
        }
    }
    return 0;
}

int directory_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

int create_directory(const char *path) {
    return mkdir(path, 0755);
}

void save_tree_to_graphviz_dot_file(const int n,
                                    const int sequence_index,
                                    int sequence_length,
                                    card sequence[sequence_length],
                                    struct node *root)
{
    char filepath[512];
    sprintf(filepath, "solution_for_n_%d/game_tree_%d.dot.gv", n, sequence_index);
    FILE *file = fopen(filepath, "w");

    if (file != NULL) {
        // add a comment header with the sequence
        fprintf(file, "# Sequence %d: ", sequence_index);
        for(int i = 0; i < sequence_length; i++) {
            fprintf(file, "%c", t(sequence[i]));
        }
        fprintf(file, "\n\n");

        // save the tree
        save_graphviz_dot_format(root, file);

        fclose(file);
    }
    else {
        perror("Failed to create file");
        printf("Game tree file not saved to disk\n");
    }
}

void save_graphviz_dot_format(struct node *root, FILE *file)
{
    if (root == NULL) return;

    fprintf(file, "digraph GameTree {\n");
    fprintf(file, "  node [shape=ellipse, style=filled, fillcolor=lightgray];\n");

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
        fprintf(file, "  node%d [label=\"Player %d drew %c\"];\n",
               curr_id,
               curr->player == player_one ? 1 : 2,
               t(curr->draw));

        // Left child
        if (curr->left && rear < NODES_MAX_CAPACITY) {
            int left_id = current_id++;
            fprintf(file, "  node%d -> node%d [label=\"L\"];\n", curr_id, left_id);

            queue[rear] = curr->left;
            ids[rear] = left_id;
            rear++;
        }

        // Right child
        if (curr->right && rear < NODES_MAX_CAPACITY) {
            int right_id = current_id++;
            fprintf(file, "  node%d -> node%d [label=\"R\"];\n", curr_id, right_id);

            queue[rear] = curr->right;
            ids[rear] = right_id;
            rear++;
        }
    }

    fprintf(file, "}\n");
}