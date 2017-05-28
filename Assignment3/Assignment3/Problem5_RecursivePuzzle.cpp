//
//  Problem5_RecursivePuzzle.cpp
//  Assignment3
//
//  Created by AC27 on 28/03/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem5_RecursivePuzzle.h"
#include <iostream>
#include "vector.h"
#include "set.h"

bool SolveRec(int index, Vector<int> &squares, Set<int> &visited) {
    if (index < 0 || index >= squares.size()) {
        return false;
    }
    if (index == squares.size() - 1) {
        return true;
    }
    if (visited.contains(index)) {
        return false;
    }
    visited.add(index);
    return SolveRec(index + squares[index], squares, visited) || SolveRec(index - squares[index], squares, visited);
}

bool Solvable(int start, Vector<int> &squares) {
    Set<int> visited;
//    visited.add(start);
    return SolveRec(start, squares, visited);
}

int Problem5_RecursivePuzzle_main() {
    Vector<int> puzzle;
    puzzle.add(3);
    puzzle.add(6);
    puzzle.add(4);
    puzzle.add(1);
    puzzle.add(3);
    puzzle.add(4);
    puzzle.add(2);
    puzzle.add(5);
    puzzle.add(3);
    puzzle.add(0);
//    Vector<int> puzzle;
//    puzzle.add(3);
//    puzzle.add(1);
//    puzzle.add(2);
//    puzzle.add(3);
//    puzzle.add(0);
    cout << Solvable(0, puzzle) << endl;
    return 0;
}
