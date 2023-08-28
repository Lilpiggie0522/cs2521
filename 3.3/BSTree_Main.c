#include <stdio.h>
#include "Tree.h"


int main(int argc, char* argv[]) {
    // Tree t = TreeCreate(10);
    // t = TreeInsert(t, 5);
    // t = TreeInsert(t, 14);

    // Tree t2 = TreeCreate(30);
    // t2 = TreeInsert(t2, 24);
    // t2 = TreeInsert(t2, 32);
    // t2 = TreeInsert(t2, 29);

    // Tree tt = TreeJoin(t, t2);
    // TreeShow(tt);
    // printf("\n");
    // tt = TreeDelete(tt, 30);
    // TreeShow(tt);
    // printf("\n");

    Tree t = TreeCreate(10);
    t = TreeInsert(t, 5);
    t = TreeInsert(t, 14);
    t = TreeInsert(t, 30);
    t = TreeInsert(t, 29);
    t = TreeInsert(t, 32);
    t = TreeInsertRoot(t, 24);
    TreeShow(t);
    printf("\n");
    return 0;
}