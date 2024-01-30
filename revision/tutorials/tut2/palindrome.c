#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool findPalin(char *s);

int main(int argc, char *argv[]) {
    char *s = "pilsip";
    bool re = findPalin(s);
    printf("result is %d\n", re);
    
    return 0;
}

bool findPalin(char *s) {
    int i = 0;
    int size = 0;
    while (s[i] != '\0') {
        printf("while ex!\n");
        size ++;
        i ++;
    }

    int j = 0;
    for (; s[j] != '\0'; j ++) {
        printf("s1 is %c, s2 is %c\n", s[j], s[size - 1 - j]);
        if (s[j] != s[size - j - 1]) {
            return false;
        }
    }
    return true;
}
