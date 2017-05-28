//
//  Problem3_CartesianProducts.cpp
//  SectionHandout3
//
//  Created by AC27 on 26/02/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem3_CartesianProducts.h"
#include "set.h"
#include "simpio.h"
#include <iostream>

struct pairT
{
    string first, second;
};

int compare(pairT a, pairT b) {
    if (a.first > b.first) {
        return 1;
    } else if (a.first < b.first) {
        return -1;
    } else if (a.second > b.second) {
        return 1;
    } else if (a.second < b.second) {
        return -1;
    } else {
        return 0;
    }
}

void print(pairT pair) {
    cout << pair.first << " " << pair.second << endl;
}

Set<pairT> CartesianProduct(Set<string> &one, Set<string> &two) {
    Set<pairT> product(compare);
    Set<string>::Iterator oneIt = one.iterator();
    while (oneIt.hasNext()) {
        string first = oneIt.next();
        Set<string>::Iterator twoIt = two.iterator();
        while (twoIt.hasNext()) {
            pairT pair;
            pair.first = first;
            pair.second = twoIt.next();
            product.add(pair);
        }
    }
    return product;
}

int Problem3_CartesianProducts_main() {
    Set<string> one;
    one.add("A");
    one.add("B");
    one.add("C");
    
    Set<string> two;
    two.add("X");
    two.add("Y");
    
    Set<pairT> product = CartesianProduct(one, two);
    product.mapAll(print);

    return 0;
}
