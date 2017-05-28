//
//  MyStack.h
//  SectionHandout7
//
//  Created by AC27 on 25/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#ifndef MyStack_h
#define MyStack_h

#include <stdio.h>
#include <iostream>
#include "vector.h"

template <typename Type>
class MyStack {
    public:
        MyStack();
        ~MyStack();
        void push(Type elem);
        Type pop();
        bool isEmpty();
        void print();
        void reverse();
    private:
        Vector<Type> elems;
};

template <typename Type>
MyStack<Type>::MyStack() {
    
}

template <typename Type>
MyStack<Type>::~MyStack() {
    
}

template <typename Type>
void MyStack<Type>::push(Type elem) {
    elems.add(elem);
}

template <typename Type>
Type MyStack<Type>::pop() {
    if (isEmpty()) {
        Error("Attempt to pop empty MyStack.");
    }
    int lastIndex = elems.size() - 1;
    Type last = elems[lastIndex];
    elems.removeAt(lastIndex);
    return last;
}

template <typename Type>
bool MyStack<Type>::isEmpty() {
    return (elems.size() == 0);
}

template <typename Type>
void MyStack<Type>::print() {
    for (int i=0; i<elems.size(); i++) {
        cout << elems[i] << ", ";
    }
    cout << endl;
}

template <typename Type>
void MyStack<Type>::reverse() {
    for (int i=0; i<elems.size()/2; i++) {
        int leftSideIdx = i;
        int rightSideIdx = elems.size()-1-leftSideIdx;
        
        Type buff = elems[leftSideIdx];
        elems[leftSideIdx] = elems[rightSideIdx];
        elems[rightSideIdx] = buff;
    }
}

#endif /* MyStack_h */
