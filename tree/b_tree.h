#include <stdio.h>
#include <stdlib.h>

#define KEY_NUM 5
#define kEY_T 3

struct BTNode {
    char isLeaf;
    int num;
    struct BTNode * ptr[KEY_NUM+1];
    int value[KEY_NUM];
};

typedef struct BTNode  BTNode;