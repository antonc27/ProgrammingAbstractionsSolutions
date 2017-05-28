//
//  Problem4_Cannonballs.cpp
//  SectionHandout3
//
//  Created by AC27 on 26/02/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem4_Cannonballs.h"
#include "simpio.h"
#include <iostream>

int Cannonball(int height) {
    if (height == 1) {
        return 1;
    }
    return height*height + Cannonball(height-1);
}

int Problem4_Cannonballs_main() {
    cout << Cannonball(3) << endl;
    
    return 0;
}
