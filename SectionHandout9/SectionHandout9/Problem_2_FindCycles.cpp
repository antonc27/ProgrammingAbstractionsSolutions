//
//  Problem_2_FindCycles.cpp
//  SectionHandout9
//
//  Created by AC27 on 03/09/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem_2_FindCycles.h"
#include "graph_utils.h"

bool IsCyclicGraph(graphT &graph) {
    Set<nodeT *> visited;
    Stack<nodeT *> traversalStack;
    
    Set<nodeT *>::Iterator itr = graph.allNodes.iterator();
    while (itr.hasNext()) {
        nodeT *next = itr.next();
        
        visited.clear();
        traversalStack.clear();
        
        visited.add(next);
        traversalStack.push(next);
        
        while (!traversalStack.isEmpty()) {
            nodeT *nextToTraverse = traversalStack.pop();
            
            Set<arcT *>::Iterator connectedItr = nextToTraverse->connected.iterator();
            while (connectedItr.hasNext()) {
                arcT *nextArc = connectedItr.next();
                nodeT *connectedWithNext = nextArc->end;
                
                if (visited.contains(connectedWithNext)) {
                    if (connectedWithNext == next) {
                        return true;
                    }
                } else {
                    visited.add(connectedWithNext);
                    traversalStack.push(connectedWithNext);
                }
            }
        }
    }
    
    return false;
}

int Problem_2_FindCycles_main() {
    InitGraphics();
    
    string imageName;
    graphT graph;
    
    string filepath = GetFilePathFromUser();
    
    ClearData(imageName, graph);
    ReadGraph(filepath, imageName, graph);
    DrawGraph(imageName, graph);
    
    cout << "This graph is cyclic: " << boolalpha << IsCyclicGraph(graph) << endl;
    
    GetLine();
    return 0;
}