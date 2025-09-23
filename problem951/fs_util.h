#pragma once

#include "problem951.h"

int save_sequences(const int n,
                   const int sequence_count,
                   const int sequence_length,
                   card sequences[sequence_count][sequence_length]);

int directory_exists(const char *path);

int create_directory(const char *path);

void save_tree_to_graphviz_dot_file(const int n,
                                    const int sequence_index,
                                    int sequence_length,
                                    card sequence[sequence_length],
                                    struct node *root);

void save_graphviz_dot_format(struct node *root, FILE *file);
