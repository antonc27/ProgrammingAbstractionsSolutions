//
//  graph_utils.cpp
//  SectionHandout9
//
//  Created by AC27 on 03/09/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "graph_utils.h"

void DrawFilledCircleWithLabel(coordT center, std::string color, std::string label = "")
{
    MovePen(center.x + CircleRadius, center.y);
    SetPenColor(color);
    StartFilledRegion(1.0);
    DrawArc(CircleRadius, 0, 360);
    EndFilledRegion();
    if (!label.empty()) {
        MovePen(center.x + CircleRadius, center.y);
        SetFont("Helvetica");
        SetPointSize(LabelFontSize);
        DrawTextString(label);
    }
}

void DrawArrow(coordT start, coordT end, string color) {
    SetPenColor(color);
    
    double d = 0.1;
    
    double nx_n = end.x - start.x;
    double ny_n = end.y - start.y;
    
    double r = sqrt(nx_n * nx_n + ny_n * ny_n);
    
    double nx = nx_n / r;
    double ny = ny_n / r;
    
    double tan = ny / nx;
    double alpha = atan(tan);
    if (nx < 0) {
        alpha += M_PI;
    }
    
    double sp_x = end.x - d * cos(alpha);
    double sp_y = end.y - d * sin(alpha);
    
    double k = 0.05;
    
    MovePen(sp_x, sp_y);
    DrawLine(-ny * k, nx * k);
    DrawLine(ny * k + d * cos(alpha), -nx * k + d * sin(alpha));
    
    MovePen(sp_x, sp_y);
    DrawLine(ny * k, -nx * k);
    DrawLine(-ny * k + d * cos(alpha), nx * k + d * sin(alpha));
}

void DrawLineBetween(coordT start, coordT end, string color)
{
    SetPenColor(color);
    MovePen(start.x, start.y);
    DrawLine(end.x - start.x, end.y - start.y);
    
    DrawArrow(start, end, color);
}

void ClearData(string &imageName, graphT &graph) {
    imageName = "";
    graph.allNodes.clear();
}

string GetFilePath(string filename) {
    string bundlePath = "./SectionHandout9.app/Contents/Resources/";
    return bundlePath + filename;
}

bool IsNext(fstream &file, string str) {
    int i = 0;
    bool isNext = false;
    for (i = 0; i < str.length(); i++) {
        int nextCh = file.get();
        if (nextCh == EOF) {
            isNext = false;
            break;
        }
        if (str[i] == (char)nextCh) {
            isNext = true;
        } else {
            isNext = false;
            break;
        }
    }
    if (isNext) {
        return true;
    } else {
        for (int j = i; j >= 0; j--) {
            file.unget();
        }
        return false;
    }
}

bool IsNextArcs(fstream &file) {
    return IsNext(file, "\rARCS") || IsNext(file, "\nARCS");
}

nodeT *findNode(graphT &graph, string nodeName) {
    Set<nodeT *>::Iterator itr = graph.allNodes.iterator();
    while (itr.hasNext()) {
        nodeT *next = itr.next();
        if (next->name == nodeName) {
            return next;
        }
    }
    return NULL;
}

void AddArc(graphT &graph, string startNodeName, string finishNodeName, double cost) {
    nodeT *startNode = findNode(graph, startNodeName);
    nodeT *finishNode = findNode(graph, finishNodeName);
    
    arcT *arc = new arcT();
    arc->start = startNode;
    arc->end = finishNode;
    
    startNode->connected.add(arc);
}

void ReadGraph(string filepath, string &imageName, graphT &graph) {
    fstream file;
    file.open(filepath.c_str());
    readGraphModeT mode = Image;
    while (file.peek() != EOF) {
        if (mode == Image) {
            file >> imageName;
            mode = Mark;
        } else if (mode == Mark) {
            string mark;
            file >> mark;
            if (mark == "NODES") {
                mode = Nodes;
            } else {
                Error("Invalid read state: Expecting valid mark");
            }
        } else if (mode == Nodes) {
            string nodeName;
            double x, y;
            file >> nodeName >> x >> y;
            
            nodeT *node = new nodeT();
            node->name = nodeName;
            node->position = {x, y};
            graph.allNodes.add(node);
            
            if (IsNextArcs(file)) {
                mode = Arcs;
            }
        } else if (mode == Arcs) {
            string startNodeName;
            string finishNodeName;
            double cost;
            file >> startNodeName >> finishNodeName >> cost;
            if (!file.fail()) {
                AddArc(graph, startNodeName, finishNodeName, cost);
            }
        } else {
            Error("Invalid read state: State not defined");
        }
    }
    file.close();
}

void ClearScreen() {
    MovePen(0, 0);
    SetPenColor("White");
    double w = GetWindowWidth();
    double h = GetWindowHeight();
    StartFilledRegion(1);
    DrawLine(w, 0);
    DrawLine(0, h);
    DrawLine(-w, 0);
    DrawLine(0, -h);
    EndFilledRegion();
}

void DrawArc(arcT *arc, string color) {
    DrawLineBetween(arc->start->position, arc->end->position, color);
}

void DrawArcFn(arcT *arc) {
    DrawArc(arc, "Black");
}

void DrawNode(nodeT *node, string color) {
    DrawFilledCircleWithLabel(node->position, color, node->name);
}

void DrawNodeFn(nodeT *node) {
    node->connected.mapAll(DrawArcFn);
    
    DrawNode(node, "Blue");
    //    Pause(0.02);
}

void DrawGraph(string imageName, graphT &graph) {
    ClearScreen();
    
    graph.allNodes.mapAll(DrawNodeFn);
}

string GetFilePathFromUser() {
    string filepath;
    while (true) {
        cout << endl << "Please enter name of graph data file: ";
        string filename = GetLine();
        filepath = GetFilePath(filename);
        
        fstream file;
        file.open(filepath.c_str());
        if (file.fail()) {
            cout << "Unable to open file named \"" << filename << "\". Please try again." << endl;
            file.clear();
            file.close();
            continue;
        }
        file.close();
        break;
    }
    return filepath;
}
