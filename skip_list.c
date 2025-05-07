//
// Created by Bence on 4/22/2025.
//

#include "skip_list.h"
#include <stdlib.h>  // malloc, calloc, free, rand
#include <stdio.h>   // printf
#include <math.h>    // log

// A maximális szint kiszámítása egy adott elemszám alapján
int calculate_max_level(int num_elements) {
    return (int)(log(num_elements) / log(1.0 / P)); // log alapon 1/P
}

// Véletlenszerű szint meghatározása egy új elemhez
int random_level(int max_level) {
    int level = 0;
    // Amíg egy véletlen dobás sikeres (valószínűség P), növeljük a szintet
    while ((float)(rand() < RAND_MAX * P) && level < max_level)
        ++level;
    return level;
}

// Új csomópont létrehozása adott adattal és szinttel
Node * create_node(int data, int level) {
    Node *node = (Node *)malloc(sizeof(Node)); // memóriafoglalás a csomóponthoz
    if (!node) return NULL; // ha sikertelen, NULL
    node->data = data; // beállítjuk az adattagot
    // forward tömb létrehozása (level + 1 hosszú), minden mutató nullázva
    node->forward = (Node **)calloc((level + 1), sizeof(Node*));
    // ha sikertelen, NULL
    if (!node->forward) {
        free(node);
        return NULL;
    }
    return node;
}

// Új skip lista létrehozása
SkipList * create_skip_list(int num_elements) {
    SkipList *list = (SkipList *)malloc(sizeof(SkipList)); // memóriafoglalás
    if (!list) return NULL;
    list->max_level = calculate_max_level(num_elements); // maximális szint kiszámítása
    list->level = 0; // kezdetben csak a 0. szint van használatban
    list->head = create_node(INT_MIN, list->max_level); // mesterséges -∞ fej csomópont
    return list;
}

// Skip lista felszabadítása a memóriából
void free_skip_list(SkipList *list) {
    Node *current = list->head;
    // végigmegyünk az alsó (0.) szinten, és minden csomópontot felszabadítunk
    while (current != NULL) {
        Node *next = current->forward[0]; // következő csomópont a 0. szinten
        free(current->forward); // forward tömb felszabadítása
        free(current); // csomópont felszabadítása
        current = next;
    }
    free(list); // végül maga a lista struktúra is felszabadul
}

// Skip lista kiíratása szintenként, fentről lefelé
void print_skip_list(SkipList *list) {
    printf("SkipList Levels:\n");
    for (int i = list->level; i >= 0; i--) { // minden szintre külön ciklus, fentről lefelé
        Node *current = list->head->forward[i]; // kezdjük a szint első eleménél
        printf("Level %d: ", i);
        while (current != NULL) { // végigmegyünk az adott szint láncolt listáján
            printf("%d ", current->data);
            current = current->forward[i]; // továbblépés a következő csomópontra ezen a szinten
        }
        printf("\n");
    }
}

// Új adat beszúrása a skip listába
void insert(SkipList *list, int data) {
    Node* update[list->max_level + 1]; // tömb, amiben eltároljuk, hol kell majd beszúrni új elemet
    Node* current = list->head;

    // Fentről lefelé haladunk, megkeressük a beszúrási helyeket minden szinten
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i]; // továbblépés, amíg kisebb az adat
        }
        update[i] = current; // eltároljuk, hol kell majd módosítani a forward mutatókat
    }

    current = current->forward[0]; // a legalsó szinten lévő lehetséges pozíció

    // Csak akkor szúrjuk be, ha az adat még nincs benne
    if (current == NULL || current->data != data) {
        int new_level = random_level(list->max_level); // új elem szintjének meghatározása

        // Ha az új szint magasabb, mint a jelenlegi legmagasabb, akkor frissítjük a listát
        if (new_level > list->level) {
            for (int i = list->level + 1; i <= new_level; i++) {
                update[i] = list->head; // új szinteken a fej lesz a beszúrási alap
            }
            list->level = new_level; // frissítjük a lista aktuális szintjét
        }

        Node* new_node = create_node(data, new_level); // új csomópont létrehozása
        // Az új csomópontot beleszúrjuk minden érintett szinten
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i]; // új elem mutat a következőre
            update[i]->forward[i] = new_node; // előző mutat az új elemre
        }
    }
}

// Keresés egy adott adat alapján
int search(SkipList *list, int data) {
    Node *current = list->head;

    // Fentről lefelé haladunk, minden szinten ameddig lehet, előrelépünk
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
    }

    current = current->forward[0]; // elérjük a lehetséges célpontot az alsó szinten

    // Visszatérünk 1-gyel (true), ha megtaláltuk, különben 0 (false)
    return current != NULL && current->data == data;
}

// Egy adott adat törlése a skip listából
void delete(SkipList *list, int data) {
    Node *update[list->max_level + 1]; // megőrizzük, hol kell módosítani a mutatókat
    Node *current = list->head;

    // Fentről lefelé, megkeressük azokat a csomópontokat, amik a törlendő elem előtt állnak
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->data < data) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0]; // elérjük a törlendő csomópontot

    // Ha valóban létezik a törlendő adat
    if (current != NULL && current->data == data) {
        // Minden szinten eltávolítjuk a csomópontot
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != current) {
                break; // ha ezen a szinten már nincs ilyen, kilépünk
            }
            update[i]->forward[i] = current->forward[i]; // kihagyjuk a csomópontot a láncból
        }

        // Ha a legfelső szintek kiürülnek, csökkentjük a lista szintjét
        while (list->level > 0 && list->head->forward[list->level] == NULL) {
            list->level--;
        }

        free(current->forward); // felszabadítjuk a forward tömböt
        free(current); // felszabadítjuk magát a csomópontot
    }
}
