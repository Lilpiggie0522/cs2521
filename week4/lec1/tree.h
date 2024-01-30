typedef struct node * Tree;

Tree createNew(int value);
Tree bstNew(void);
Tree bstInsert(Tree t, int value);
int bstSize(Tree t);
Tree rotateRight(Tree t);
Tree rotateLeft(Tree t);
void printTree(Tree t);
Tree partition(Tree t, int i);
Tree rebalance(Tree t);
Tree periodicRebalancingInsert(Tree t, int value);
Tree insertAtRoot(Tree t, int value);
int avlHeight(Tree t);
Tree avlInsert(Tree t, int value);
int max(struct node *left, struct node *right);
Tree avlInsertHeight(Tree t, int value);