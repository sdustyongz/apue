#include <b_tree.h>

BTNode * root;

BTNode * createNode(){
    BTNode * node = malloc(sizeof(BTNode));
    if(node != NULL){
        node->isLeaf = 0;
        node->num = 0;
        return node;
    }
    return NULL;
}

BTNode * createThree(){
    if(root  == NULL){
        root = createNode();
    }
    return root;
}



BTNode * search(BTNode * node ,int key){
    int i = node->num-1;
    while(key < node->value[i] && i >= 0){
        i--;
    }
    if(key == node->value[i]) return node;
    search(node->ptr[i+1])
}

void split_node(BTNode * parent ,int index){
    BTNode * child = parent->ptr[index];
    int t = KEY_NUM/2+1;
    BTNode * node  = createNode();
    int i = KEY_NUM-1;
    for(;i > t-1;i--){
        node->value[i-t] = child->value[i];
        child->value[i] = 0;
        node->ptr[i-t+1] = child->ptr[i+1];
        child->ptr[i+1] = NULL;
    }
    node->ptr[0] = child->ptr[t];
    child->ptr[t] = NULL;
    child->num = t-1;
    node->num = t-1;

    i = parent->num-1;
    int key = child->value[t-1]; 
    while(key <parent->value[i] && i >= 0){
        parent->vlaue[i+1] = parent->value[i];
        parent->ptr[i+2] = parent->value[i+1];
        i--;
    }
    parent->value[i+1] = key;
    parent->ptr[i+2] = node;
}