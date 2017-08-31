#include <iostream>
#include "extgraph.h"
#include "simpio.h"
#include "genlib.h"
#include "set.h"
#include "map.h"
#include <fstream>
#include <math.h>

const double CircleRadius = 0.05;
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

void DrawLineBetween(coordT start, coordT end, string color)
{
    SetPenColor(color);
    MovePen(start.x, start.y);
    DrawLine(end.x - start.x, end.y - start.y);
    
    double d = 0.2;
    
    double nx_n = end.x - start.x;
    double ny_n = end.y - start.y;
    
    double r = sqrt(nx_n * nx_n + ny_n * ny_n);
    
    double nx = nx_n / r;
    double ny = ny_n / r;
    
    double tan = ny / nx;
    double alpha = atan(tan);
//    alpha *= -tan / fabs(tan);
    
    double sp_x = end.x - d * cos(alpha);
    double sp_y = end.y - d * sin(alpha);
    
    MovePen(sp_x, sp_y);
    DrawLine(-ny * d, nx * d);
    
    MovePen(sp_x, sp_y);
    DrawLine(ny * d, -nx * d);
}

void ClearData(string &imageName, Map<nodeT *> &graph) {
    imageName = "";
    graph.clear();
}

string GetFilePath(string filename) {
    string bundlePath = "./SectionHandout9.app/Contents/Resources/";
    return bundlePath + filename;
}

enum readGraphModeT {
    Mark,
    Image,
    Nodes,
    Arcs
};

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

void AddArc(Map<nodeT *> &graph, string startNodeName, string finishNodeName, double cost) {
    nodeT *startNode = graph[startNodeName];
    nodeT *finishNode = graph[finishNodeName];
    
    arcT *arc = new arcT();
    arc->start = startNode;
    arc->end = finishNode;
    
    startNode->connected.add(arc);
}

void ReadGraph(string filepath, string &imageName, Map<nodeT *> &graph) {
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
            graph.add(nodeName, node);
            
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

void DrawNodeFn(string key, nodeT *node) {
    node->connected.mapAll(DrawArcFn);
    
    DrawNode(node, "Blue");
    //    Pause(0.02);
}

void DrawGraph(string imageName, Map<nodeT *> &graph) {
    ClearScreen();
    
    graph.mapAll(DrawNodeFn);
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

int main() 
{
    InitGraphics();
    
    string imageName;
    Map<nodeT *> graph;
    
    string filepath = GetFilePathFromUser();
    
    ClearData(imageName, graph);
    ReadGraph(filepath, imageName, graph);
    DrawGraph(imageName, graph);
    
    GetLine();
	return 0;
}
