//
// Created by Bence on 5/7/2025.
//

#ifndef RUNNING_COMPETITION_H
#define RUNNING_COMPETITION_H
// Beérkezési idők: 320, 280, 450, 300, 290, 600
// Megkérdezzük: van-e olyan idő, hogy 300?
// Töröljük a 450-es hibás adatot
// Kiírjuk az összes rendezett időt
// Megnézzük, hányan jöttek be 280 és 320 között
#include"skip_list.h"
int count_in_range(SkipList *list, int low, int high);
void demo_exercise();
#endif //RUNNING_COMPETITION_H
