#ifndef TREE_H
#define TREE_H

typedef struct Node* Tree;

Tree TreeCreate(int n);
Tree TreeInsert(Tree s, int n);

void TreeShow(Tree s);
#endif 