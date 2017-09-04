//
//  Problem_4_WordLadderGraph.cpp
//  SectionHandout9
//
//  Created by AC27 on 04/09/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem_4_WordLadderGraph.h"
#include "graph_utils.h"
#include "lexicon.h"
#include "queue.h"
#include "stack.h"

bool HasOneDifferentChar(string one, string two) {
    if (one.length() != two.length()) {
        return false;
    }
    int diffs = 0;
    for (int i = 0; i < one.length(); i++) {
        if (one[i] != two[i]) {
            diffs++;
        }
    }
    return (diffs == 1);
}

void AddWordToGraph(string word, graphT &graph) {
    nodeT* node = findNode(graph, word);
    if (node == NULL) {
        node = new nodeT();
        node->name = word;
        graph.allNodes.add(node);
    } else {
        return;
    }
    
    Set<nodeT *>::Iterator nodeItr = graph.allNodes.iterator();
    while (nodeItr.hasNext()) {
        nodeT* nextNode = nodeItr.next();
        if (HasOneDifferentChar(node->name, nextNode->name)) {
            AddArc(graph, node->name, nextNode->name, 1);
            AddArc(graph, nextNode->name, node->name, 1);
        }
    }
}

void ConstructGraph(graphT &graph, Lexicon &lex) {
    lex.mapAll(AddWordToGraph, graph);
}

Stack<nodeT *> FindShortestLaddder(graphT &graph, nodeT start, nodeT end) {
    Stack<nodeT *> shortest;
    
    nodeT *startP = &start;
    nodeT *endP = &end;
    
    Set<nodeT *> visited;
//    visited.add(startP);
    
    Queue<nodeT *> queue;
    queue.enqueue(startP);
    
    while (!queue.isEmpty()) {
        nodeT *nextNode = queue.dequeue();
        
        if (!visited.contains(nextNode)) {
            visited.add(nextNode);
            shortest.push(nextNode);
            
            if (nextNode == endP) {
                break;
            }
            
            Set<arcT *> connected = nextNode->connected;
            Set<arcT *>::Iterator arcItr = connected.iterator();
            while (arcItr.hasNext()) {
                arcT *arc = arcItr.next();
                nodeT *nextNextNode = arc->end;
                if (!visited.contains(nextNextNode)) {
//                    visited.add(nextNextNode);
                    queue.enqueue(nextNextNode);
                }
            }
        }
    }
    
    return shortest;
}

void PrintLadder(Stack<nodeT *> ladder) {
    while (!ladder.isEmpty()) {
        cout << ladder.pop()->name;
        if (ladder.size() > 0) {
            cout << " -> ";
        }
    }
    cout << endl;
}

int Problem_4_WordLadderGraph_main() {
    Lexicon lex;
    lex.add("cake");
    lex.add("came");
    lex.add("camp");
    lex.add("damp");
    lex.add("dame");
    lex.add("dime");
    lex.add("dike");
    lex.add("like");
    lex.add("lake");
    lex.add("lame");
    lex.add("lamp");
    lex.add("limp");
    lex.add("lime");
    
    graphT wordGraph;
    ConstructGraph(wordGraph, lex);
    
    nodeT *start = findNode(wordGraph, "came");
    nodeT *end = findNode(wordGraph, "lime");
    
    Stack<nodeT *> shortest = FindShortestLaddder(wordGraph, *start, *end);
    cout << "Shortest ladder: ";
    PrintLadder(shortest);
    
    return 0;
}