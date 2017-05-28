//
//  Problem2_SimpleClass.cpp
//  SectionHandout6
//
//  Created by AC27 on 23/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem2_SimpleClass.h"
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "MyRectangle.h"

using namespace std;

int Problem2_SimpleClass_main()
{
    MyRectangle rect = MyRectangle(0, 0, 1, 1);
    
    cout << rect.toString() << endl;
    cout << "Perimiter: " << rect.getPerimeter() << endl;
    
    rect.scale(3);
    cout << rect.toString() << endl;
    
    cout << "Area after scale: " << rect.getArea() << endl;
    
    return 0;
}
