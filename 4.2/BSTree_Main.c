#include <stdio.h>
#include "Tree.h"
#include <stdlib.h>

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

    // Tree t = TreeCreate(10);
    // t = TreeInsert(t, 5);
    // t = TreeInsert(t, 14);
    // t = TreeInsert(t, 30);
    // t = TreeInsert(t, 29);
    // t = TreeInsert(t, 32);
    // t = TreeInsertRoot(t, 24);
    Tree t = InsertAVL(NULL, 4);
    t = InsertAVL(t, 2);

    // t = InsertAVL(t, 10);
    // t = InsertAVL(t, 8);
    // t = InsertAVL(t, 12);
    // t = InsertAVL(t, 9);

    t = InsertAVL(t, 8);
    t = InsertAVL(t, 1);
    t = InsertAVL(t, 5);
    t = InsertAVL(t, 3);
    t = InsertAVL(t, 7);
    TreeShow(t);
    printf("\n");
    return 0;
}