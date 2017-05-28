//
//  Problem5_MoreTemplatizedFunctions.cpp
//  SectionHandout6
//
//  Created by AC27 on 25/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem5_MoreTemplatizedFunctions.h"
#include <iostream>
#include "vector.h"
#include "set.h"

template <typename ElemType>
void RemoveDuplicates(Vector<ElemType> &v, int (Cmp)(ElemType, ElemType) = OperatorCmp) {
    Set<ElemType> s(Cmp);
    Vector<ElemType> vCopy;
    for (int i=0; i<v.size(); i++) {
        ElemType next = v[i];
        if (!s.contains(next)) {
            vCopy.add(next);
            s.add(next);
        }
    }
    v = vCopy;
}

void PrintVector(Vector<int> &v) {
    for (int i=0; i<v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
}

template <typename ElemType>
int CmpAbs(ElemType a, ElemType b) {
    return OperatorCmp(a*a, b*b);
}


int Problem5_MoreTemplatizedFunctions_main() {
    Vector<int> v;
    v.add(1);
    v.add(2);
    v.add(3);
    v.add(4);
    v.add(2);
    v.add(3);
    v.add(3);
    
    PrintVector(v);
    RemoveDuplicates(v);
    PrintVector(v);
    
    Vector<int> vB;
    vB.add(1);
    vB.add(2);
    vB.add(-3);
    vB.add(4);
    vB.add(-2);
    vB.add(3);
    vB.add(3);
    
    PrintVector(vB);
    RemoveDuplicates(vB, CmpAbs);
    PrintVector(vB);
    
    return 0;
}
