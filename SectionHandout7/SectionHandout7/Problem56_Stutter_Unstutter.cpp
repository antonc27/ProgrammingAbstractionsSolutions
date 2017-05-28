//
//  Problem56_Stutter_Unstutter.cpp
//  SectionHandout7
//
//  Created by AC27 on 25/05/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem56_Stutter_Unstutter.h"
#include <iostream>
#include "genlib.h"

struct Node {
    int value;
    Node* next;
};

void AddValue(Node *&node, int value) {
    Node *newNode = new Node();
    newNode->value = value;
    newNode->next = NULL;
    
    if (node == NULL) {
        node = newNode;
    } else {
        Node *endNode = node;
        while (endNode->next != NULL) {
            endNode = endNode->next;
        }
        endNode->next = newNode;
    }
}

void PrintList(Node *node) {
    cout << "(";
    while (node != NULL) {
        cout << node->value;
        if (node->next != NULL) {
            cout << " ";
        }
        node = node->next;
    }
    cout << ")" << endl;
}

void Stutter(Node *&node) {
    Node *currentNode = node;
    while (currentNode != NULL) {
        Node *duplicate = new Node();
        duplicate->value = currentNode->value;
        duplicate->next = currentNode->next;
        
        currentNode->next = duplicate;
        currentNode = duplicate->next;
    }
}

void Unstutter(Node *&node) {
    Node *currentNode = node;
    while (currentNode != NULL && currentNode->next != NULL) {
        if (currentNode->value == currentNode->next->value) {
            Node *duplicate = currentNode->next;
            currentNode->next = currentNode->next->next;
            delete duplicate;
        }
        currentNode = currentNode->next;
    }
}

int Problem56_Stutter_Unstutter_main() {
    Node *n = NULL;
    AddValue(n, 11);
    AddValue(n, 5);
    AddValue(n, 21);
    AddValue(n, 7);
    AddValue(n, 7);
    
    PrintList(n);
    
    Stutter(n);
    PrintList(n);
    
    cout << endl;
    
    Node *dn = NULL;
    AddValue(dn, 5);
    AddValue(dn, 5);
    AddValue(dn, 22);
    AddValue(dn, 37);
    AddValue(dn, 89);
    AddValue(dn, 89);
    AddValue(dn, 15);
    AddValue(dn, 15);
    AddValue(dn, 22);
    PrintList(dn);
    
    Unstutter(dn);
    PrintList(dn);
    
    return 0;
}
