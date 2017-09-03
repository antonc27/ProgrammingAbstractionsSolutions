//
//  graph_utils.h
//  SectionHandout9
//
//  Created by AC27 on 03/09/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#ifndef graph_utils_h
#define graph_utils_h

#include <iostream>
#include "extgraph.h"
#include "simpio.h"
#include "set.h"
#include "stack.h"
#include <fstream>
#include <math.h>

const double CircleRadius = 0.03;
const int LabelFontSize = 9;

struct coordT {
    double x, y;
};

struct arcT;

struct nodeT {
    string name;
    Set<arcT *> connected;
    
    coordT position;
};

struct arcT {
    nodeT * start;
    nodeT * end;
};

struct graphT {
    Set<nodeT *> allNodes;
};

void DrawFilledCircleWithLabel(coordT center, std::string color, std::string label);

void DrawArrow(coordT start, coordT end, string color);

void DrawLineBetween(coordT start, coordT end, string color);

void ClearData(string &imageName, graphT &graph);

string GetFilePath(string filename);

enum readGraphModeT {
    Mark,
    Image,
    Nodes,
    Arcs
};

bool IsNext(fstream &file, string str);

bool IsNextArcs(fstream &file);

nodeT *findNode(graphT &graph, string nodeName);

void AddArc(graphT &graph, string startNodeName, string finishNodeName, double cost);

void ReadGraph(string filepath, string &imageName, graphT &graph);

void ClearScreen();

void DrawArc(arcT *arc, string color);

void DrawArcFn(arcT *arc);

void DrawNode(nodeT *node, string color);

void DrawNodeFn(nodeT *node);

void DrawGraph(string imageName, graphT &graph);

string GetFilePathFromUser();

#endif /* graph_utils_h */
