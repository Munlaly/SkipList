// Skip lista fejléce – típusdefiníciók és függvénydeklarációk

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

static float P = 0.5;            // A valószínűségi konstans a szintek meghatározásához (tipikusan 0.5)


// Skip lista csomópont struktúrája
typedef struct Node {
    int data;                   // Az adott csomópontban tárolt adat
    // Tömb ami a csomópont szomszédait minden szinten, Null ha nincs szomszéd vagya csomópont nincs azon a szinten
    struct Node **forward;
} Node;


// Skip lista struktúra – tárolja az aktuális és maximális szintet, valamint a fejcsomópontot
typedef struct {
    int level;                 // A skip lista jelenlegi legmagasabb aktív szintje
    int max_level;            // Elméletileg megengedett legmagasabb szint (előre kiszámított)
    Node *head;               // A lista fejcsomópontja, amely minden szintre mutat
} SkipList;


// Függvénydeklarációk

int calculate_max_level(int num_elements);        // Meghatározza a max szintet az elemek száma alapján
int random_level(int max_level);                  // Véletlenszerű szint generálása új elemhez
Node* create_node(int data, int level);           // Új csomópont létrehozása
SkipList* create_skip_list(int num_elements);     // Skip lista létrehozása
void free_skip_list(SkipList *list);              // Skip lista teljes felszabadítása

void print_skip_list(SkipList *list);             // Skip lista kiíratása szintenként

void insert(SkipList *list, int data);            // Új adat beszúrása
int search(SkipList *list, int data);             // Keresés egy adott értékre
void delete(SkipList *list, int data);            // Adott adat törlése

#endif //SKIP_LIST_H
