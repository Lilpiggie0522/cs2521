#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct recommendation {
    char *name;
    int numMutualFriends;
};

int main(int argc, char *argv[]) {
    struct recommendation *recs = calloc(6, sizeof(*recs));
    recs[0] = malloc(sizeof(struct recommendation));
    strcpy(recs[0].name, "piggie");
    printf("%s\n", recs[0].name);
}

