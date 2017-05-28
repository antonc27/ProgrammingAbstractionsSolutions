//
//  Problem6_Append.cpp
//  SectionHandout4
//
//  Created by AC27 on 14/04/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem6_Append.h"
#include <iostream>
#include "simpio.h"
#include "Problem4_LinkedListWarmup.h"

void AppendList(Cell *&listA, Cell *listB) {
    if (listA == NULL) {
        listA = listB;
        return;
    }
    AppendList(listA->next, listB);
}

int Problem6_Append_main() {
    Cell *listA = NULL;
    AddToList(listA, 1);
    AddToList(listA, 4);
    AddToList(listA, 6);
    
    Cell *listB = NULL;
    AddToList(listB, 3);
    AddToList(listB, 19);
    AddToList(listB, 2);
    
    PrintList(listA);
    PrintList(listB);
    
    AppendList(listA, listB);
    PrintList(listA);
    
    return 0;
}
