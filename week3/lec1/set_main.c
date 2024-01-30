#include <stdio.h>
#include "Sets.h"


int main(int argc, char *argv[]) {
    Set s = SetNew();
    SetInsert(s, 12);
    SetInsert(s, 13);
    SetShow(s);
    return 0;
}