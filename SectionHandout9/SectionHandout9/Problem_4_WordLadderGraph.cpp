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

void PrintLadder(Stack<nodeT *> ladder) {
    while (!ladder.isEmpty()) {
        cout << ladder.pop()->name;
        if (ladder.size() > 0) {
            cout << " <- ";
        }
    }
    cout << endl;
}

Stack<nodeT *> FindShortestLaddder(graphT &graph, nodeT *startP, nodeT *endP) {
    Set<nodeT *> visited;
    
    Queue<Stack<nodeT *>> queue;
    
    Stack<nodeT *> initial;
    initial.push(startP);
    queue.enqueue(initial);
    
    while (!queue.isEmpty()) {
        Stack<nodeT *> path = queue.dequeue();
//        cout << "Dequeued: ";
//        PrintLadder(path);
        
        nodeT *endPathNode = path.peek();
        
        if (!visited.contains(endPathNode)) {
            visited.add(endPathNode);
            
            if (endPathNode == endP) {
                return path;
            }
            
            Set<arcT *> connected = endPathNode->connected;
            Set<arcT *>::Iterator arcItr = connected.iterator();
            while (arcItr.hasNext()) {
                arcT *arc = arcItr.next();
                nodeT *nextNextNode = arc->end;
                if (!visited.contains(nextNextNode)) {
                    
                    Stack<nodeT *> newPath = path;
                    newPath.push(nextNextNode);
                    queue.enqueue(newPath);
                }
            }
        }
    }
    
    return Stack<nodeT *>();
}

Stack<nodeT *> FindLongestLadder(graphT & graph, nodeT *start) {
    Stack<nodeT *> longest;
    
    Set<nodeT *> visited;
    
    Stack<Stack<nodeT *>> stack;
    
    Stack<nodeT *> initial;
    initial.push(start);
    stack.push(initial);
    
    while (!stack.isEmpty()) {
        Stack<nodeT *> path = stack.pop();
        //        cout << "Dequeued: ";
        //        PrintLadder(path);
        
        nodeT *endPathNode = path.peek();
        
        if (!visited.contains(endPathNode)) {
            visited.add(endPathNode);
            
            if (path.size() > longest.size()) {
                longest = path;
            }
            
            Set<arcT *> connected = endPathNode->connected;
            Set<arcT *>::Iterator arcItr = connected.iterator();
            while (arcItr.hasNext()) {
                arcT *arc = arcItr.next();
                nodeT *nextNextNode = arc->end;
                if (!visited.contains(nextNextNode)) {
                    Stack<nodeT *> newPath = path;
                    newPath.push(nextNextNode);
                    stack.push(newPath);
                }
            }
        }
    }
    
    return longest;
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
    
    Stack<nodeT *> shortest = FindShortestLaddder(wordGraph, start, end);
    cout << "Shortest ladder from " << start->name << " to " << end->name << " : ";
    PrintLadder(shortest);
    
    Stack<nodeT *> longest = FindLongestLadder(wordGraph, start);
    cout << "Longest ladder from " << start->name << ": ";
    PrintLadder(longest);
    
    return 0;
}