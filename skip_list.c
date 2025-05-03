//
// Created by Bence on 4/22/2025.
//

#include "skip_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



int calculate_max_level(int num_elements) {
    return (int)(log(num_elements) / log(1.0 / P));
}

int random_level(int max_level) {
    int level = 0;

    while ((float)(rand() < RAND_MAX * P) && level < max_level)
        ++level;
    return level;
}

Node * create_node(int data, int level) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = data;
    node->forward = ( Node **)calloc((level + 1), sizeof(Node*));
    if (!node->forward) return NULL;
    return node;
}

SkipList * create_skip_list(int num_elements) {
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    if (!list) return NULL;
    list->max_level = calculate_max_level(num_elements);
    list->level = 0;
    list->head = create_node(INT_MIN, list->max_level);
    return list;
}

void free_skip_list(SkipList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->forward[0];
        free(current->forward);
        free(current);
        current = next;
    }
    free(list);
}

void print_skip_list(SkipList *list) {
    printf("SkipList Levels:\n");
    for (int i = list->level; i >= 0; i--) {
        Node *current = list->head->forward[i];
        printf("Level %d: ", i);
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->forward[i];
        }
        printf("\n");
    }
}

void insert(SkipList *list, int data) {
    Node* update[list->max_level + 1];
    Node* current = list->head;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current == NULL || current->data != data) {
        int new_level = random_level(list->max_level);

        if (new_level > list->level) {
            for (int i = list->level + 1; i <= new_level; i++) {
                update[i] = list->head;
            }
            list->level = new_level;
        }

        Node* new_node = create_node(data, new_level);
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
    }
}

int search(SkipList *list, int data) {
    Node *current = list->head;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    return current != NULL && current->data == data;
}

void delete(SkipList *list, int data) {
    Node *update[list->max_level + 1];
    Node *current = list->head;

    for (int i = list->level; i >= 0; i--) {

        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != NULL && current->data == data) {

        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        while (list->level > 0 && list->head->forward[list->level] == NULL) {
            list->level--;
        }

        free(current->forward);
        free(current);
    }
}
