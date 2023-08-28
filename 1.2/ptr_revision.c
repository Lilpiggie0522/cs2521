#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int age;
    char name[99];
};

void updateAge(struct person *tom, int newAge);

int main (int argc, char* argv[]) {
    // if (argc > 1) { 
    //     int counter = 0;
    //     while (argv[counter] != NULL) {
    //         printf("%s\n", argv[counter]);
    //         counter ++;
    //     }
    // } else {
    //     printf("%d arguments!\n", argc);
    // }
    
    // 1
    char arr[] = "Piggie";
    char* ptr = arr;
    printf("%c\n", *ptr);

    //2
    char (*ptr2)[] = &arr;
    printf("%c\n", (*ptr2)[4]);

    struct person* tom_ptr = (struct person*)malloc(sizeof(struct person));
    strcpy(tom_ptr->name, "Jane");
    tom_ptr->age = 13;
    printf("%s is %d years old\n", tom_ptr->name, tom_ptr->age);
    updateAge(tom_ptr, 22);
    printf("%s is %d years old\n", tom_ptr->name, tom_ptr->age);
    free(tom_ptr);
    return 0;
}

void updateAge(struct person *tom, int newAge) {
    tom->age = newAge;
}

