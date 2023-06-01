#include <stdio.h>

struct node {
    long  key;
    void * value;
    struct node * left;
    struct node * right;
    struct node * parent;
};

typedef struct node  Node;

void insert(Node * root, int key, void * val);
void delete(Node * root, int key);
Node * search(Node * root, int key);

