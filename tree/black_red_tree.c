#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int key;
    void *value;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    short red;
};
typedef struct Node Node;

struct Tree
{
    Node *root;
    int size;
};
typedef struct Tree Tree;
void insert_balance(Node *node, Tree * tree);
int tree_height(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    if (left_height > right_height)
    {
        return left_height + 1;
    }
    return right_height + 1;
}
Tree *createTree()
{
    Tree * tree = malloc(sizeof(Tree));
    memset(tree, 0, sizeof(Tree));
    return tree;
}

Node *createNode(int key, void *value)
{
    Node *node = malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    node->key = key;
    node->value = value;
    node->red = 1;
    return node;
}

Node *insert(Tree* tree, int key, void *value)
{
    Node *node = createNode(key, value);
    if (tree->root == NULL)
    {
        node->red = 0;
        tree->root = node;
        return node;
    }
    Node *k = tree->root;
    while (k != NULL)
    {
        if (k->key > key)
        {
            if (k->left == NULL)
                break;
            k = k->left;
        }
        else if (k->key == key)
            return k;
        else
        {
            if (k->right == NULL)
                break;
            k = k->right;
        }
    }
    if (k->key > key)
        k->left = node;
    else
        k->right = node;
    node->parent = k;
    insert_balance(node, tree);
}
Node *right_rotate(Node *node, Tree *tree)
{
    Node *lk = node->left;
    if(lk != NULL)
         lk->parent = node->parent;
    if (node == tree->root)
        tree->root = lk;
    if (node->parent->right == node)
        node->parent->right = lk;
    else
        node->parent->left = lk;
    node->parent->left = node->left;
    node->left = lk->right;
    if (node->left != NULL)
        node->left->parent = node;
    node->parent = lk;
    lk->right = node;
    return node->parent;
}

Node *left_rotate(Node *node, Tree *tree)
{
    Node *rk = node->right;
    rk->parent = node->parent;
    if (node == tree->root)
    {
        tree->root = rk;
    }
    else
    {
        if (node->parent->right == node)
            node->parent->right = rk;
        else
            node->parent->left = rk;
    }
    node->right = rk->left;
    if (node->right != NULL)
        node->right->parent = node;

    node->parent = rk;
    rk->left = node;
    return node->parent;
}

void insert_balance(Node *node, Tree * tree){
    Node * parent  = node->parent;
    if(parent == NULL){
         node->red = 0;
        return;
    }
    if(parent->red == 0) return;
    //parent->parent 一定存在，因为root为黑色
    Node * uncle;
    if(parent->parent->left == parent)
        uncle = parent->parent->right;
    else uncle = parent->parent->left;
    if(uncle != NULL && uncle->red == 1){
        parent->red = 0;
        parent->parent->red = 1;
        uncle->red = 0;
        insert_balance(parent->parent,tree);
    }else{
        //叔父节点为黑
        if(node == parent->left){
            parent->red = 0;
            parent->parent->red = 1;
            right_rotate(parent->parent, tree);
        }else{
            left_rotate(parent,tree);
            node->red = 0;
            node->parent->red = 1;
            right_rotate(node->parent, tree);
        }
    }
}
void print1(Tree *tree)
{
    Node *root = tree->root;
    Node *empty_node = malloc(sizeof(Node));
    memset(empty_node, 0, sizeof(Node));
    Node *p = root;
    int height = tree_height(root);
    int level = 0;
    int level_num = pow(2, level);
    Node **node_queue = malloc(sizeof(Node *) * level_num);
    int first_space = (pow(2, height - 1) * 3 - 1) / 2;
    int i;
    node_queue[0] = root;
    while (level < height)
    {
        for (i = 0; i < first_space; i++)
            printf("   ");
        int distance = pow(2, (height - level - 1)) + 1;
        for (i = 0; i < level_num; i++)
        {
            if (node_queue[i] != empty_node)
                printf("%d-%d" , node_queue[i]->key,node_queue[i]->red);
            else
                printf("---");
            for (int j = 0; j < distance; j++)
                printf("   ");
        }
        level++;
        Node **temp_queue = malloc(sizeof(Node *) * pow(2, level));
        for (i = 0; i < level_num; i++)
        {
            temp_queue[2 * i] = node_queue[i]->left == NULL ? empty_node : node_queue[i]->left;
            temp_queue[2 * i + 1] = node_queue[i]->right == NULL ? empty_node : node_queue[i]->right;
        }
        level_num = pow(2, level);
        first_space -= 2;
        free(node_queue);
        node_queue = temp_queue;
        printf("\n");
    }
    free(empty_node);
}
int main(int argc, char *argv[]){
    Tree * tree = createTree();
    insert(tree,1,NULL);
    insert(tree,10,NULL);
    insert(tree,20,NULL);
    insert(tree,30 ,NULL);
    insert(tree,40,NULL);
   print1(tree); 
}
