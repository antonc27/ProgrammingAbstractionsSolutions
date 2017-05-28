//
//  PartA_SortDetective.cpp
//  Assignment5
//
//  Created by AC27 on 04/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "PartA_SortDetective.h"

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "mysterysort.h"
#include "vector.h"
#include "random.h"
#include <ctime>

#include "graphics.h"
#include "extgraph.h"

Vector<int> GenerateRandomVector(int size, int low, int high) {
    Vector<int> v;
    for (int i = 0; i < size; i++) {
        v.add(RandomInteger(low, high));
    }
    return v;
}

void PrintVector(Vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i != v.size()-1) {
            cout << ", ";
        }
    }
    cout << endl << endl;
}

void Reverse(Vector<int> &v) {
    int n = v.size();
    for (int i=0; i<n/2; i++) {
        int tmp = v[i];
        v[i] = v[n-1-i];
        v[n-1-i] = tmp;
    }
}

double MeasureSort(Vector<int> v, void (Sort)(Vector<int> &nums, double maxSecs)) {
    double start = double(clock()) / CLOCKS_PER_SEC;
    
    int times = 100;
    for (int i = 0; i < times; i++) {
        Vector<int> copy = v;
        Sort(copy, -1);
    }
    
    double finish = double(clock()) / CLOCKS_PER_SEC;
    double elapsed = finish - start;
    return elapsed / times;
}

void MeasureSortOnDoubling(Vector<int> v, Vector<int> v2, void (Sort)(Vector<int> &nums, double maxSecs)) {
    double time = MeasureSort(v, Sort);
    double time2 = MeasureSort(v2, Sort);
    double ratio = time2 / time;
    
    cout << time << endl;
    cout << time2 << endl;
    cout << ratio << endl;
}

void DrawBar(double x, double y, double width, double height) {
    MovePen(x, y);
    StartFilledRegion(1.0);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
    EndFilledRegion();
}

void PlotVector(Vector<int> &v, int max, double initX, double initY, double width, double height) {
    int size = v.size();
    double step = width / size;
    double x = initX;
    double y = initY;
    
    for (int i = 0; i < size; i++) {
        int elem = v[i];
        double coef = (double)elem / max;
        DrawBar(x, y, step, coef * height);
        x += step;
    }
}

typedef void(*FunctionPointer)(Vector<int> &, double);
FunctionPointer FunctionPointers[] = { MysterySort1, MysterySort2, MysterySort3, MysterySort4, MysterySort5 };

double maxSecs[] = { 0.01, 0.0001, 0.0001, 0.01, 0.01 };

#define WINDOW_WIDTH 2*7.0
#define WINDOW_HEIGHT 2*5.0

#define N_SORTS 5
#define N_PLOTS (N_SORTS + 1)
#define HEIGHT_PER_PLOT WINDOW_HEIGHT / N_PLOTS

int PartA_SortDetective_main()
{
    //    Randomize();
    //    int size = 1000;
    ////    Vector<int> v = GenerateRandomVector(size, -100, 100);
    //    Vector<int> v2 = GenerateRandomVector(2 * size, -100, 100);
    ////    MysterySort3(v2);
    ////    Reverse(v2);
    //    Vector<int> v;
    //    for (int i = 0; i < size; i++) {
    //        v.add(v2[i]);
    //    }
    //
    //    for (int i = 0; i < N_SORTS; i++) {
    //        MeasureSortOnDoubling(v, v2, FunctionPointers[i]);
    //        cout << endl;
    //    }
    
    SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    InitGraphics();
    SetPenColor("Dark Gray");
    
    int size = 2000;
    int max = 100;
    Vector<int> v = GenerateRandomVector(size, 1, max);
    //    MysterySort3(v);
    //    Reverse(v);
    
    //    MovePen(1.0, 1.0);
    //    DrawLine(1.0, 1.0);
    
    double x = 0;
    double y = WINDOW_HEIGHT - HEIGHT_PER_PLOT;
    
    PrintVector(v);
    PlotVector(v, max, x, y, WINDOW_WIDTH, HEIGHT_PER_PLOT);
    
    for (int i = 0; i < N_SORTS; i++) {
        Vector<int> vCopy = v;
        FunctionPointers[i](vCopy, maxSecs[i]);
        
        PrintVector(vCopy);
        y -= HEIGHT_PER_PLOT;
        PlotVector(vCopy, max, x, y, WINDOW_WIDTH, HEIGHT_PER_PLOT);
    }
    
    return 0;
}
