//
//  Problem_3_TreeEqual.cpp
//  SectionHandout8
//
//  Created by AC27 on 29/07/2017.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem_3_TreeEqual.h"
#include <iostream>
#include "tree.h"

bool IsTreeEqual(nodeT *firstTree, nodeT *secondTree) {
    if (firstTree == NULL && secondTree == NULL) {
        return true;
    }
    if (firstTree == NULL || secondTree == NULL) {
        return false;
    }
    if (firstTree->key == secondTree->key) {
        return IsTreeEqual(firstTree->left, secondTree->left) && IsTreeEqual(firstTree->right, secondTree->right);
    }
    return false;
}

int Problem_3_TreeEqual_main() {
    
    nodeT *firstTree = NULL;
    InsertNode(firstTree, "Benton");
    InsertNode(firstTree, "Carter");
    InsertNode(firstTree, "Greene");
    InsertNode(firstTree, "Hathaway");
    InsertNode(firstTree, "Morganstern");
    InsertNode(firstTree, "Ross");
    InsertNode(firstTree, "Weaver");
    
    nodeT *secondTree = NULL;
    InsertNode(secondTree, "Benton");
    InsertNode(secondTree, "Carter");
    InsertNode(secondTree, "Greene");
    InsertNode(secondTree, "Hathaway");
    InsertNode(secondTree, "Morganstern");
    InsertNode(secondTree, "Ross");
    InsertNode(secondTree, "Weaver");
    
    cout << boolalpha << "Is tree equal: " << IsTreeEqual(firstTree, secondTree) << endl;
    
    return 0;
}
