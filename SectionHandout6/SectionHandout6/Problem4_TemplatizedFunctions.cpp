//
//  Problem4_TemplatizedFunctions.cpp
//  SectionHandout6
//
//  Created by AC27 on 24/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem4_TemplatizedFunctions.h"
#include "queue.h"
#include <iostream>

template <typename ElemType>
void Filter(Queue<ElemType> &queue, bool (Predicate)(ElemType)) {
    int size = queue.size();
    for (int i=0; i<size; i++) {
        ElemType next = queue.dequeue();
        if (!Predicate(next)) {
            queue.enqueue(next);
        }
    }
}

template <typename ElemType>
void PrintQueue(Queue<ElemType> queue, string (ToString)(ElemType)) {
    while (!queue.isEmpty()) {
        ElemType next = queue.dequeue();
        cout << ToString(next) << endl;
    }
}

struct recordingT {
    string title;
    string genre;
    int rating;
};

bool IsBadAnimation(recordingT show)
{
    return (show.genre == "animation" && show.rating < 8);
}

string ToString(recordingT show) {
    return show.title + " " + show.genre;
}

int Problem4_TemplatizedFunctions_main() {
    Queue<recordingT> q;
    q.enqueue({"MIB", "action", 9});
    q.enqueue({"Raskolbas", "animation", 3});
    q.enqueue({"Interstellar", "sci-fi", 10});
    
    PrintQueue(q, ToString);
    cout << endl;
    
    Filter(q, IsBadAnimation);
    PrintQueue(q, ToString);
    
    return 0;
}
