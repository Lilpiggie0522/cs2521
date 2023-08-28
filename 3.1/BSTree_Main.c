#include <stdio.h>
#include "Tree.h"


int main(int argc, char* argv[]) {
    Tree t = TreeCreate(5);
    t = TreeInsert(t, 4);
    t = TreeInsert(t, 7);
    t = TreeInsert(t, 2);
    t = TreeInsert(t, 6);
    t = TreeInsert(t, 8);
    TreeShow(t);
    return 0;
}