//
//  Problem3_CountVotes.cpp
//  Assignment3
//
//  Created by AC27 on 28/03/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem3_CountVotes.h"
#include <iostream>
#include "genlib.h"
#include "vector.h"

int CountCriticalVotesRec(Vector<int> &blocks, int currentBlockIndex, int targetBlockValue, int sumA, int sumB) {
    if (currentBlockIndex >= blocks.size()) {
        if (sumA > sumB) {
            if (sumB + targetBlockValue > sumA) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if (sumA + targetBlockValue > sumB) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    
    int currentBlockValue = blocks[currentBlockIndex];
    
    return CountCriticalVotesRec(blocks, currentBlockIndex + 1, targetBlockValue, sumA + currentBlockValue, sumB) + CountCriticalVotesRec(blocks, currentBlockIndex + 1, targetBlockValue, sumA, sumB + currentBlockValue);
}

int CountCriticalVotes(Vector<int> &blocks, int blockIndex) {
    Vector<int> blocksCopy = blocks;
    int blockValue = blocksCopy[blockIndex];
    blocksCopy.removeAt(blockIndex);
    
    return CountCriticalVotesRec(blocksCopy, 0, blockValue, 0, 0);
}

int Problem3_CountVotes_main() {
    Vector<int> v;
    v.add(4);
    v.add(2);
    v.add(7);
    v.add(4);
    cout << CountCriticalVotes(v, 1) << endl;
    return 0;
}
