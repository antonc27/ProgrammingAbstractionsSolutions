//
//  mazelib.cpp
//  SectionHandout4
//
//  Created by AC27 on 09/04/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "mazelib.h"
#include "genlib.h"
//#include "simpio.h"
#include <iostream>
#include <fstream>
#include "grid.h"

using namespace std;

//const char CORNER_CHAR = '+';
const char HORIZ_WALL_CH = '-';
const char VERT_WALL_CH = '|';
const char OPEN_SPACE_CH = ' ';
const char MARK_CH = 'x';
const char START_CH = 'S';

Grid<char> maze;

pointT LocalToReal(pointT pLocal) {
    return {pLocal.x / 2, pLocal.y / 2};
}

pointT RealToLocal(pointT pReal) {
    return {pReal.x * 2 + 1, pReal.y * 2 + 1};
}

void PrintMaze() {
    for (int i = 0; i < maze.numRows(); i++) {
        for (int j = 0; j < maze.numCols(); j++) {
            cout << maze.getAt(i, j);
        }
        cout << endl;
    }
    cout << endl;
}

void ReadMazeMap(string filename) {
    ifstream inFile(filename.c_str());
    int rows = (int)count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n') + 1;
    inFile.close();

    inFile.open(filename.c_str());
    maze.~Grid();
    int lines = 0;
    while (inFile.peek() != EOF) {
        string line;
        getline(inFile, line);
        
        if (maze.numCols() == 0 || maze.numRows() == 0) {
            maze.resize(rows, line.length());
        }
        for (int i = 0; i < line.length(); i++) {
            maze.setAt(lines, i, line[i]);
        }
        lines++;
    }
    inFile.close();
}

pointT GetStartPosition() {
    for (int i = 0; i < maze.numRows(); i++) {
        for (int j = 0; j < maze.numCols(); j++) {
            if (maze.getAt(i, j) == START_CH) {
                return LocalToReal({j, i});
            }
        }
    }
    return {-1, -1};
}

bool OutsideMaze(pointT pt) {
    pointT localPt = RealToLocal(pt);
    return (localPt.x < 0 || localPt.x >= maze.numCols() || localPt.y < 0 || localPt.y >= maze.numRows());
}

bool WallExists(pointT pt, directionT dir) {
    pointT localPt = RealToLocal(pt);
    switch (dir) {
        case North: localPt.y++; break;
        case East: localPt.x++; break;
        case South: localPt.y--; break;
        case West: localPt.x--; break;;
    }
    char probableWall = maze.getAt(localPt.y, localPt.x);
    return (probableWall == HORIZ_WALL_CH || probableWall == VERT_WALL_CH);
}

void MarkSquare(pointT pt) {
    pointT localPt = RealToLocal(pt);
    maze.setAt(localPt.y, localPt.x, MARK_CH);
}

void UnmarkSquare(pointT pt) {
    pointT localPt = RealToLocal(pt);
    maze.setAt(localPt.y, localPt.x, OPEN_SPACE_CH);
}

bool IsMarked(pointT pt) {
    pointT localPt = RealToLocal(pt);
    return (maze.getAt(localPt.y, localPt.x) == MARK_CH);
}

int MarkedPathLength() {
    int length = 0;
    for (int i = 0; i < maze.numRows(); i++) {
        for (int j = 0; j < maze.numCols(); j++) {
            if (maze.getAt(i, j) == MARK_CH) {
                length++;
            }
        }
    }
    return length;
}
