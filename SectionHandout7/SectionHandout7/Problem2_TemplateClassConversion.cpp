//
//  Problem2_TemplateClassConversion.cpp
//  SectionHandout7
//
//  Created by AC27 on 25/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem2_TemplateClassConversion.h"
#include <iostream>
#include "Mob.h"

int Problem2_TemplateClassConversion_main() {
    Mob<int> m;
    
    m.enqueue(1);
    m.enqueue(2);
    m.enqueue(3);
    
    int size = m.size();
    for (int i=0; i<size; i++) {
        cout << m.dequeue() << endl;
    }
    
    return 0;
}
