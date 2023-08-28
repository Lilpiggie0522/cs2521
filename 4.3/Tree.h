#ifndef TREE_H
#define TREE_H

typedef struct Node* Tree;
typedef struct B_Node* B_Tree;

Tree TreeCreate(int n);
Tree TreeInsert(Tree s, int n);
Tree TreeJoin(Tree tree1, Tree tree2);
void TreeShow(Tree s);
Tree TreeDelete(Tree s, int n);
Tree TreeTraverse(Tree s, int n, Tree last);
Tree TreeShiftRight(Tree root);
Tree TreeShiftLeft(Tree root);
Tree TreeInsertRoot(Tree root, int n);
Tree InsertAVL(Tree root, int n);
int max(Tree s);
B_Tree Search_Node(B_Tree root, int n);
#endif 