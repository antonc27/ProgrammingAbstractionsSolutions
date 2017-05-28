//
//  Problem1_CountWays.cpp
//  Assignment3
//
//  Created by AC27 on 18/03/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem1_CountWays.h"
#include <iostream>
#include "genlib.h"

const int SMALL_STRIDE = 1;
const int LARGE_STRIDE = 2;

int CountWays(int numStairs) {
    if (numStairs < 0) {
        return 0;
    }
    if (numStairs == 0) {
        return 1;
    }
    
    return CountWays(numStairs - SMALL_STRIDE) + CountWays(numStairs - LARGE_STRIDE);
}

int Problem1_CountWays_main() {
    cout << CountWays(4) << endl;
    return 0;
}
