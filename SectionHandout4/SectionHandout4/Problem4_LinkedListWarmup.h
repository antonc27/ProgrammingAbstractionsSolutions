//
//  Problem4_LinkedListWarmup.hpp
//  SectionHandout4
//
//  Created by AC27 on 10/04/17.
//  Copyright © 2017 AC27. All rights reserved.
//

struct Cell {
    Cell *next;
    int value;
};

int Problem4_LinkedListWarmup_main();

void PrintList(Cell *list);
void AddToList(Cell *&list, int value);
