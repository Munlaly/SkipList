//
// Created by Bence on 4/22/2025.
//

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

static float P = 0.5;

typedef struct Node {
    int data;
    struct Node **forward;
} Node;

typedef struct {
    int level;
    int max_level;
    Node *head;
} SkipList;
int calculate_max_level(int num_elements);
int random_level(int max_level);
Node* create_node(int data, int level);
SkipList* create_skip_list(int num_elements);
void free_skip_list(SkipList *list);

void print_skip_list(SkipList *list);

void insert(SkipList *list, int data);
int search(SkipList *list, int data);
void delete(SkipList *list, int data);
#endif //SKIP_LIST_H
