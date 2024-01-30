#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Item;

struct Node {
    struct Node *next;
    char *key;
};
struct Node *appendBucket(struct Node *bucket, char key[]);
struct Node **emptyBucket(struct Node *buckets[], int size);
void radix(char *arr[], int m, int size);

int main(int argc, char* argv[]) {
    char *arr[] = {"cba", "dbb", "aqz"};
    radix(arr, 3, 3);
    return 0;
}

void radix(char *arr[], int m, int size) {
    struct Node **buckets = NULL;
    for (int i = 0; i < m; i ++) {
        buckets[i] = malloc(sizeof(struct Node));
    }
    
    for (int i = m; i > 0; i --) { /// m = 2
        buckets = emptyBucket(buckets, 3);
        for (int key = 0; key < size; key ++) {
            if (arr[key][i] == 'c') {
                appendBucket(buckets[2], arr[key]);
            }
            if (arr[key][i] == 'b') {
                appendBucket(buckets[1], arr[key]);
            }
            if (arr[key][i] == 'a') {
                appendBucket(buckets[0], arr[key]);
            }
        }

        for (int bucketNum = 0; bucketNum < m; bucketNum ++) {
            struct Node *ptr = buckets[bucketNum];
            while (ptr != NULL) {
                strcpy(arr[bucketNum], ptr->key);
                ptr = ptr->next;
            }
        }
    }
}

struct Node **emptyBucke(struct Node **buckets, int size) {
    for (int i = 0; i < size; i ++) {
        free(buckets[i]);
    }
    struct Node **new_buckets = malloc(sizeof(struct Node) * size);
    for (int i = 0; i < size; i ++) {
        new_buckets[i] = malloc(sizeof(struct Node));
        new_buckets[i]->key = malloc(sizeof(char) * 4);
        new_buckets[i]->next = NULL;
    }
    return new_buckets;
}

struct Node *appendBucket(struct Node *bucket, char key[]) {
    if (bucket == NULL) {
        struct Node *new = malloc(sizeof(struct Node)); 
        new->key = malloc(sizeof(char) * 4);
        strcpy(new->key, key);
        new->next = NULL;
        return new;
    }
    struct Node *curr = bucket;
    while ((curr->next) != NULL) {
        curr = curr->next;
    }
    struct Node *new = malloc(sizeof(struct Node));
    new->key = malloc(sizeof(char) * 4);
    strcpy(new->key, key);
    new->next = NULL;
    curr->next = new;
    return bucket;
}