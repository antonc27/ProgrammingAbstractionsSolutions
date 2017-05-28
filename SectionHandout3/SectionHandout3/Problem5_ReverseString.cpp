//
//  Problem5_ReverseString.cpp
//  SectionHandout3
//
//  Created by AC27 on 27/02/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem5_ReverseString.h"
#include "simpio.h"
#include <iostream>

string ReverseStringRecursive(string str) {
    int length = str.length();
    if (length == 1) {
        return str;
    }
    return str.substr(length - 1) + ReverseStringRecursive(str.substr(0, length - 1));
}

string ReverseStringIterative(string str) {
    string result = "";
    for (int i = str.length()-1; i >= 0; i--) {
        result += str[i];
    }
    return result;
}

int Problem5_ReverseString_main() {
    cout << ReverseStringIterative("ABCDsdf") << endl;
    
    return 0;
}
