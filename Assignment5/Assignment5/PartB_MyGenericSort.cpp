//
//  PartB_MyGenericSort.cpp
//  Assignment5
//
//  Created by AC27 on 10/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "PartB_MyGenericSort.h"
#include "PartA_SortDetective.h"

#include <iostream>
#include "vector.h"
#include "set.h"

int OperatorCmpStr(string one, string two) {
    if (one.size() == two.size()) {
        for (int i=0; i<one.size(); i++) {
            char charOne = one[i];
            char charTwo = two[i];
            if (OperatorCmp(charOne, charTwo) < 0) {
                return -1;
            }
        }
        return 0;
    } else if (one.size() < two.size()) {
       return -1;
    } else {
      return 1;
    }
}

int sumSetOfInts(Set<int> &set) {
    int sum = 0;
    Set<int>::Iterator itr = set.iterator();
    while (itr.hasNext()) {
        sum += itr.next();
    }
    return sum;
}

int OperatorCmpSetOfInts(Set<int> one, Set<int> two) {
    int sumOne = sumSetOfInts(one);
    int sumTwo = sumSetOfInts(two);
    return OperatorCmp(sumOne, sumTwo);
}

template <typename Type>
bool IsSorted(Vector<Type> &v, int (cmpFn)(Type, Type)) {
    for (int i=1; i<v.size(); i++) {
        if (cmpFn(v[i], v[i-1]) < 0) {
            return false;
        }
    }
    return true;
}

template <typename Type>
bool BogoSort(Vector<Type> &vInitial, Vector<Type> &vPermutated, int (cmpFn)(Type, Type)) {
    if (vInitial.size() == 0) {
        return IsSorted(vPermutated, cmpFn);
    }
    for (int i=0; i<vInitial.size(); i++) {
        Vector<Type> vI = vInitial;
        Vector<Type> vP = vPermutated;
        vP.add(vI[i]);
        vI.removeAt(i);
        if (BogoSort(vI, vP, cmpFn)) {
            vPermutated = vP;
            return true;
        }
    }
    return false;
}

template <typename Type>
void Sort(Vector<Type> &v, int (cmpFn)(Type, Type) = OperatorCmp) {
    Vector<Type> vCI = v;
    Vector<Type> vCP;
    if (BogoSort(vCI, vCP, cmpFn)) {
        v = vCP;
    }
}

void PrintStrVector(Vector<string> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    cout << endl;
}

void PrintSetOfIntsVector(Vector<Set<int>> &v) {
    for (int i = 0; i < v.size(); i++) {
        Set<int> &si = v[i];
        Set<int>::Iterator itr = si.iterator();
        cout << "{ ";
        while (itr.hasNext()) {
            cout << itr.next() << ", ";
        }
        cout << "}" << endl;
    }
    cout << endl;
}

int PartB_MyGenericSort_main() {
    Vector<int> v;
    v.add(3);
    v.add(5);
    v.add(-1);
    v.add(0);
    v.add(100);
    v.add(42);
    v.add(789);
    v.add(7);
    PrintVector(v);
    Sort(v);
    PrintVector(v);
    
    Vector<string> vS;
    vS.add("a");
    vS.add("c");
    vS.add("b");
    vS.add("really long string");
    vS.add("str");
    
    PrintStrVector(vS);
    Sort(vS, OperatorCmpStr);
    PrintStrVector(vS);
    
    Vector<Set<int>> vSI;
    Set<int> v3;
    v3.add(101);
    vSI.add(v3);
    Set<int> v2;
    v2.add(2);
    v2.add(8);
    vSI.add(v2);
    Set<int> v1;
    v1.add(1);
    v1.add(2);
    v1.add(3);
    vSI.add(v1);
    
    PrintSetOfIntsVector(vSI);
    Sort(vSI, OperatorCmpSetOfInts);
    PrintSetOfIntsVector(vSI);
    
    return 0;
}
