//
//  MyRectangle.h
//  SectionHandout6
//
//  Created by AC27 on 22/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#ifndef MyRectangle_h
#define MyRectangle_h

#include <stdio.h>
#include <string>

class MyRectangle {
    
public:
    MyRectangle(double x, double y, double width, double height);
    ~MyRectangle();
    double getPerimeter();
    double getArea();
    std::string toString();
    void transalte(double dx, double dy);
    void scale(double coef);
    
private:
    double x;
    double y;
    double width;
    double height;
};

#endif /* MyRectangle_h */
