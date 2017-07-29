//
//  Problem_4_TrimLeaves.cpp
//  SectionHandout8
//
//  Created by AC27 on 29/07/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem_4_TrimLeaves.h"
#include "tree.h"

bool IsLeaf(nodeT *node) {
    return node != NULL && node->left == NULL && node->right == NULL;
}

void TrimLeaves(nodeT * & tree) {
    if (tree == NULL) {
        return;
    }
    if (IsLeaf(tree->left)) {
        delete tree->left;
        tree->left = NULL;
    }
    if (IsLeaf(tree->right)) {
        delete tree->right;
        tree->right = NULL;
    }
    TrimLeaves(tree->left);
    TrimLeaves(tree->right);
}

int Problem_4_TrimLeaves_main() {
    
    nodeT *tree = NULL;
    InsertNode(tree, "Jan");
    InsertNode(tree, "Cindy");
    InsertNode(tree, "Bobby");
    InsertNode(tree, "Greg");
    InsertNode(tree, "Marsha");
    InsertNode(tree, "Peter");
    InsertNode(tree, "Tiger");
    
    DisplayTree(tree);
    cout << endl;
    
    TrimLeaves(tree);
    DisplayTree(tree);
    
    return 0;
}
