#ifndef TREE_H
#define TREE_H

typedef struct Node* Tree;

Tree TreeCreate(int n);
Tree TreeInsert(Tree s, int n);
Tree TreeJoin(Tree tree1, Tree tree2);
void TreeShow(Tree s);
Tree TreeDelete(Tree s, int n);
Tree TreeTraverse(Tree s, int n, Tree last);
#endif 