//
//  Problem_5_BalancedTrees.cpp
//  SectionHandout8
//
//  Created by AC27 on 29/07/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem_5_BalancedTrees.h"
#include <iostream>
#include "tree.h"

int TreeHeight(nodeT *t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + max(TreeHeight(t->left), TreeHeight(t->right));
}

bool IsBalanced(nodeT *t) {
    if (t == NULL) {
        return true;
    }
    int leftHeight = TreeHeight(t->left);
    int rightHeight = TreeHeight(t->right);
    if (abs(leftHeight - rightHeight) < 2) {
        return IsBalanced(t->left) && IsBalanced(t->right);
    }
    return false;
}

void PrintTreeInfo(nodeT *t) {
    cout << boolalpha;
    cout << "Tree height: " << TreeHeight(t);
    cout << " ";
    cout << "Is balanced: " << IsBalanced(t);
    cout << endl;
}

int Problem_5_BalancedTrees_main() {
    
    nodeT *balancedTree = NULL;
    InsertNode(balancedTree, "Grumpy");
    InsertNode(balancedTree, "Doc");
    InsertNode(balancedTree, "Bashful");
    InsertNode(balancedTree, "Dopey");
    InsertNode(balancedTree, "Sleepy");
    InsertNode(balancedTree, "Happy");
    InsertNode(balancedTree, "Sneezy");
    
    PrintTreeInfo(balancedTree);
    
    nodeT *unbalancedTree = NULL;
    InsertNode(unbalancedTree, "Bashful");
    InsertNode(unbalancedTree, "Doc");
    InsertNode(unbalancedTree, "Dopey");
    InsertNode(unbalancedTree, "Grumpy");
    InsertNode(unbalancedTree, "Happy");
    InsertNode(unbalancedTree, "Sleepy");
    InsertNode(unbalancedTree, "Sneezy");
    
    PrintTreeInfo(unbalancedTree);
    
    return 0;
}
