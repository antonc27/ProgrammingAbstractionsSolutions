//
//  MyRectangle.cpp
//  SectionHandout6
//
//  Created by AC27 on 22/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "MyRectangle.h"
#include <sstream>

MyRectangle::MyRectangle(double x, double y, double width, double height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

MyRectangle::~MyRectangle() {
    
}

double MyRectangle::getPerimeter() {
    return 2 * (width + height);
}

double MyRectangle::getArea() {
    return width * height;
}

std::string MyRectangle::toString() {
    std::ostringstream stringStream;
    stringStream << "{x: " << x << ", y: " << y << ", w: " << width << ", h: " << height << "}";
    return stringStream.str();
}

void MyRectangle::transalte(double dx, double dy) {
    x += dx;
    y += dy;
}

void MyRectangle::scale(double coef) {
    width *= coef;
    height *= coef;
}
