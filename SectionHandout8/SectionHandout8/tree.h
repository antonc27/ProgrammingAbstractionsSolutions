#ifndef tree_h
#define tree_h

#include "genlib.h"

struct nodeT
{
    string key;
    nodeT * left;
    nodeT * right;
};

void InsertNode(nodeT * & t, string key) {
    if (t == NULL) {
        t = new nodeT;
        t->key = key;
        t->left = t->right = NULL;
        return;
    }
    if (key == t->key) return;
    if (key < t->key) {
        InsertNode(t->left, key);
    } else {
        InsertNode(t->right, key);
    }
}

#endif /* tree_h */
