
#define TREE_NODE_COUNT 4

struct node{
    int values[TREE_NODE_COUNT+1];
    struct node * children[TREE_NODE_COUNT+2];
    struct node * parent;
    int size;
};

typedef struct node  Node;

