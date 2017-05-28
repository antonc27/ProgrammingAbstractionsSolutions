//
//  Problem1_FillRegion.cpp
//  SectionHandout4
//
//  Created by AC27 on 10/04/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem1_FillRegion.h"
#include <iostream>
#include <fstream>
#include "genlib.h"
#include "simpio.h"
#include "grid.h"

using namespace std;

const char whiteChar = '0';
const char blackChar = '1';

enum pixelStateT { White, Black };

struct pointT {
    int row, col;
};

void PrintScreen(Grid<pixelStateT> &screen) {
    cout << endl;
    for (int i = 0; i < screen.numRows(); i++) {
        for (int j = 0; j < screen.numCols(); j++) {
            pixelStateT pixel = screen.getAt(i, j);
            cout << ((pixel == White) ? whiteChar : blackChar);
        }
        cout << endl;
    }
    cout << endl;
}

void FillRegion(pointT pt, Grid<pixelStateT> &screen) {
    int rows = screen.numRows();
    int cols = screen.numCols();
    if (pt.col < 0 || pt.col >= cols || pt.row < 0 || pt.row >= rows) {
        return;
    }
    if (screen.getAt(pt.row, pt.col) == Black) {
        return;
    }
    screen.setAt(pt.row, pt.col, Black);
    FillRegion({pt.row-1, pt.col}, screen);
    FillRegion({pt.row+1, pt.col}, screen);
    FillRegion({pt.row, pt.col-1}, screen);
    FillRegion({pt.row, pt.col+1}, screen);
}

int Problem1_FillRegion_main()
{
    string filename = "./SectionHandout4.app/Contents/Resources/home_num.txt";
    ifstream file;
    file.open(filename.c_str());
    
    Grid<pixelStateT> grid(24, 19);
    
    int currentRow = 0;
    string line;
    while (file.peek() != EOF) {
        getline(file, line);
        //        cout << line << endl;
        
        for (int i = 0; i < line.length(); i++) {
            grid.setAt(currentRow, i, (line[i] == whiteChar) ? White : Black);
        }
        currentRow++;
    }
    
    PrintScreen(grid);
    
    FillRegion({1, 1}, grid);
    
    PrintScreen(grid);
    
    file.close();
    return 0;
}
