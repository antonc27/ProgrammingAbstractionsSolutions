//
//  Problem3_FunctionPointersAndTemplates.cpp
//  SectionHandout6
//
//  Created by AC27 on 23/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem3_FunctionPointersAndTemplates.h"
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"

template <typename ElemType>
int CmpDefault(ElemType a, ElemType b) {
    if (a < b) {
        return -1;
    } else if (a == b) {
        return 0;
    } else {
        return 1;
    }
}

template <typename ElemType>
ElemType FindMax(Vector<ElemType> v, int (Cmp)(ElemType, ElemType) = CmpDefault) {
    ElemType max = v[0];
    for (int i=1; i<v.size(); i++) {
        if (Cmp(max, v[i]) < 0) {
            max = v[i];
        }
    }
    return max;
}

struct Car {
    string name;
    int weight;
    int numAirbags;
};

int CmpCars(Car a, Car b) {
    if (a.numAirbags == b.numAirbags) {
        return CmpDefault(a.weight, a.weight);
    }
    return CmpDefault(a.numAirbags, b.numAirbags);
}

int Problem3_FunctionPointersAndTemplates_main() {
    Vector<int> v;
    v.add(-89);
    v.add(100);
    v.add(0);
    v.add(2);
    cout << FindMax(v) << endl;
    
    Vector<Car> cars;
    cars.add({"ford", 150, 1});
    cars.add({"niva", 100, 1});
    cars.add({"peagot", 100, 0});
    
    cout << FindMax(cars, CmpCars).name << endl;
    return 0;
}
