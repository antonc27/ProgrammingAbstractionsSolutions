//
//  Problem7_OldFashionedMeasuring.cpp
//  SectionHandout3
//
//  Created by AC27 on 27/02/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem7_OldFashionedMeasuring.h"
#include "simpio.h"
#include "vector.h"
#include <iostream>

bool IsMeasurable(int target, Vector<int> &weights) {
    if (weights.isEmpty()) {
        return (target == 0);
    }
    int w = weights.getAt(0);
    weights.removeAt(0);
    return IsMeasurable(target + w, weights) || IsMeasurable(target - w, weights) || IsMeasurable(target, weights);
}

int Problem7_OldFashionedMeasuring_main() {
    Vector<int> sampleWeights;
    sampleWeights.add(1);
    sampleWeights.add(3);
    
    cout << (IsMeasurable(5, sampleWeights) ? "YES" : "NO") << endl;
    
    return 0;
}
