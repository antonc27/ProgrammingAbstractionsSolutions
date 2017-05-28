//
//  Mob.h
//  SectionHandout7
//
//  Created by AC27 on 25/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#ifndef Mob_h
#define Mob_h

#include <stdio.h>
#include "vector.h"
#include "random.h"

template <typename Type>
class Mob {
    public:
        Mob();
        void enqueue(Type newElem);
        Type dequeue();
        int size();
    private:
        Vector<Type> elems;
};

template <typename Type>
Mob<Type>::Mob() {
    Randomize();
}

template <typename Type>
int Mob<Type>::size() {
    return elems.size();
}

template <typename Type>
void Mob<Type>::enqueue(Type newElem)
{
    elems.add(newElem);
}

template <typename Type>
Type Mob<Type>::dequeue()
{
    int elemNum = RandomInteger(0, elems.size()-1);
    Type value = elems[elemNum];
    elems.removeAt(elemNum);
    return value;
}

#endif /* Mob_h */
