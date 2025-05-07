//
// Created by Bence on 5/7/2025.
//

#include "running_competition.h"
#include<stdio.h>

int count_in_range(SkipList *list, int low, int high) {
    Node *current = list->head;

    // Navigálunk a low értékhez legközelebb eső elemhez
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->data < low) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    int count = 0;
    while (current && current->data <= high) {
        count++;
        current = current->forward[0];
    }

    return count;
}

void demo_exercise() {

    SkipList *list = create_skip_list(100);
    if (!list) {
        printf("Nem sikerult létrehozni a skip listat.\n");
        return ;
    }

    // 1. Beszúrás
    int times[] = {320, 280, 450, 300, 290, 600};
    for (int i = 0; i < 6; ++i) {
        insert(list, times[i]);
    }

    printf("Rendezett szintidok:\n");
    print_skip_list(list);

    // 2. Keresés
    int target = 300;
    printf("\nKereses %d idore: %s\n", target, search(list, target) ? "megtalalva" : "nincs benne");

    // 3. Törlés
    delete(list, 450);
    printf("\nToroltuk a 450-es hibas adatot.\n");
    print_skip_list(list);

    // 4. Tartományos számlálás
    int low = 280, high = 320;
    int count = count_in_range(list, low, high);
    printf("\nBeerkezesek szama %d es %d masodperc kozott: %d\n", low, high, count);

    // 5. Felszabadítás
    free_skip_list(list);
}

