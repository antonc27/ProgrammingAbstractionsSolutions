//
//  Problem1_ClientSideVsImplementationSide.cpp
//  SectionHandout7
//
//  Created by AC27 on 25/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem1_ClientSideVsImplementationSide.h"
#include "MyStack.h"

template <typename Type>
void ReverseMyStack(MyStack<Type> &stack) {
    MyStack<Type> reversed;
    while (!stack.isEmpty()) {
        reversed.push(stack.pop());
    }
    stack = reversed;
}

int Problem1_ClientSideVsImplementationSide_main() {
    MyStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.print();
    
    s.pop();
    s.print();
    
    s.push(3);
    s.reverse();
    s.print();
    
    ReverseMyStack(s);
    s.print();
    
    return 0;
}
