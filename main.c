#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skip_list.h"
#include"running_competition.h"
void test();
int main(void) {
   //test();
    demo_exercise();
    return 0;
}
void test() {
    srand(time(0));

    // Create skip list with an estimated number of elements
    SkipList *list = create_skip_list(20);

    // Insert elements
    printf("Inserting elements: 3, 6, 7, 9, 12, 19, 17, 26, 21, 25\n");
    int values_to_insert[] = {3, 6, 7, 9, 12, 19, 17, 26, 21, 25};
    int size = sizeof(values_to_insert) / sizeof(values_to_insert[0]);

    for (int i = 0; i < size; i++) {
        insert(list, values_to_insert[i]);
    }

    // Print the skip list
    print_skip_list(list);

    // Search for values
    int search_values[] = {19, 5, 26, 15};
    printf("\nSearching for values:\n");
    for (int i = 0; i < 4; i++) {
        int found = search(list, search_values[i]);
        printf("Value %d %s found.\n", search_values[i], found ? "was" : "was NOT");
    }

    // Delete a few values
    printf("\nDeleting values: 3, 7, 19\n");
    int values_to_delete[] = {3, 7, 19};
    for (int i = 0; i < 3; i++) {
        delete(list, values_to_delete[i]);
    }

    // Print the skip list after deletions
    printf("\nSkip list after deletions:\n");
    print_skip_list(list);

    // Free memory
    free_skip_list(list);

}