#include <stdio.h>

int main (int argc, char* argv[]) {
    char input;
    scanf("%c", &input);
    switch(input) {
        case('w'):
            printf("its a w!\n");
            break;
        
        case('s'):
            printf("its s!\n");
            break;

        case('a'):
            printf("its a!\n");
            break;

        case('d'):
            printf("its d!\n");
            break; 
        
        default: printf("Nothing detected!\n");
    }
    return 0;
}