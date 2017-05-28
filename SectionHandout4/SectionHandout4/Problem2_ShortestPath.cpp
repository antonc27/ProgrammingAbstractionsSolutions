//
//  Problem2_ShortestPath.cpp
//  SectionHandout4
//
//  Created by AC27 on 10/04/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem2_ShortestPath.h"
#include <iostream>
#include "genlib.h"
#include "mazelib.h"

using namespace std;

static const int NoSolution = 10000;

pointT AdjacentPoint(pointT pt, directionT dir) {
    pointT newpt = pt;
    switch (dir) {
        case North: newpt.y++; break;
        case East: newpt.x++; break;
        case South: newpt.y--; break;
        case West: newpt.x--; break;;
    }
    return newpt;
}

int ShortestPathLength(pointT pt) {
    int minPathLength = NoSolution;
    if (OutsideMaze(pt)) {
//        PrintMaze();
        return 0;
    }
    if (IsMarked(pt)) {
        return NoSolution;
    }
    MarkSquare(pt);
    for (int i = 3; i >= 0; i--) {
        directionT dir = directionT(i);
        if (!WallExists(pt, dir)) {
            int len = ShortestPathLength(AdjacentPoint(pt, dir));
            minPathLength = min(minPathLength, len);
        }
    }
    UnmarkSquare(pt);
    if (minPathLength == NoSolution) {
        return NoSolution;
    } else {
        return minPathLength+1;
    }
}

int Problem2_ShortestPath_main()
{
    ReadMazeMap("/Users/Nyadesu/Desktop/Courses/ProgrammingAbstractions/Projects/Xcode/SectionHandout4/SectionHandout4/maze.txt");
    
    PrintMaze();
    
    int shortestPathLength = ShortestPathLength(GetStartPosition());
    if (shortestPathLength != NoSolution) {
        cout << "The shortest solution path has length of " << shortestPathLength << "." << endl;
    } else {
        cout << "No solution exists." << endl;
    }
    cout << endl;
    
//    PrintMaze();
    
    return 0;
}
