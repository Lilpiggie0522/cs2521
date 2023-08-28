#include <stdio.h>
#include "Set.h"

int main(int argc, char* argv[]) {
    Set s = SetCreate();
    for (int i = 1; i < 26; i += 2) {
        SetInsert(s, i);
    }
    SetInsert(s, 13);
    // SetDeletion(s, 99);
    SetShow(s);
    printf("\n");
}