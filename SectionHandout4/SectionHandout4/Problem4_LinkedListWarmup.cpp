//
//  Problem4_LinkedListWarmup.cpp
//  SectionHandout4
//
//  Created by AC27 on 10/04/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem4_LinkedListWarmup.h"
#include <iostream>
#include "simpio.h"
#include "vector.h"

//struct Cell {
//    Cell *next;
//    int value;
//};

void PrintList(Cell *list) {
    Cell *cur = list;
    while (cur != NULL) {
        cout << cur->value;
        if (cur->next) {
            cout << ", ";
        }
        cur = cur->next;
    }
    cout << endl;
}

void PrintVector(Vector<int> &vec) {
    for (int i=0; i<vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size()-1) {
            cout << ", ";
        }
    }
    cout << endl;
}

void AddToList(Cell *&list, int value) {
    Cell *newCell = new Cell;
    newCell->value = value;
    
    if (!list) {
        list = newCell;
        return;
    }
    
    Cell *last = list;
    while (last->next) {
        last = last->next;
    }
    last->next = newCell;
}

Cell * ConvertToListIter(Vector<int> vector) {
    Cell *list = NULL;
    for (int i=0; i<vector.size(); i++) {
        AddToList(list, vector[i]);
    }
    return list;
}

Cell * ConvertToListRec(Vector<int> vector) {
    if (vector.size() == 1) {
        Cell *list = new Cell;
        list->value = vector[0];
        return list;
    } else {
        int valueToAppend = vector[0];
        vector.removeAt(0);
        Cell *prev = ConvertToListRec(vector);
        Cell *list = new Cell;
        list->value = valueToAppend;
        list->next = prev;
        return list;
    }
}

int SumListIter(Cell *list) {
    int sum = 0;
    for (Cell *cell = list; cell!=NULL; cell=cell->next) {
        sum += cell->value;
    }
    return sum;
}

int SumListRec(Cell *list) {
    if (!list->next) {
        return list->value;
    } else {
        return list->value + SumListRec(list->next);
    }
}

int Problem4_LinkedListWarmup_main() {
//    Cell *list = NULL;
//    AddToList(list, 3);
//    AddToList(list, 2);
//    AddToList(list, 5);
    
    Vector<int> v;
    v.add(5);
    v.add(2);
    v.add(3);
    
//    PrintVector(v);
    
//    Cell *list = ConvertToListIter(v);
    Cell *list = ConvertToListRec(v);
    PrintList(list);
    
    cout << SumListIter(list) << endl;
    cout << SumListRec(list) << endl;
    
    return 0;
}
