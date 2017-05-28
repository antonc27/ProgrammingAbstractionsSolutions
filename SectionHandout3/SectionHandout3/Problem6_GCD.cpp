//
//  Problem6_GCD.cpp
//  SectionHandout3
//
//  Created by AC27 on 27/02/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem6_GCD.h"
#include "simpio.h"
#include <iostream>

int GCD(int x, int y) {
    int rem = x % y;
    if (rem == 0) {
        return y;
    } else {
        return GCD(y, rem);
    }
}

int Problem6_GCD_main() {
    cout << GCD(70, 5) << endl;
    
    return 0;
}
