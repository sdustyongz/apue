#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    long key;
    void *value;
    struct node *left;
    struct node *right;
    struct node *parent;
    /**
     * 以本节点为根的树的高度，默认为1
     */
    int height;
};

typedef struct node Node;

struct Tree
{
    Node *root;
};
typedef struct Tree Tree;

Node *create_node(int key, void *value)
{
    Node *node = malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    node->key = key;
    node->value = value;
    node->height = 1;
    return node;
}

int node_height(Node *node)
{
    if (node == NULL)
        return 0;
    int max_height = 0;
    if (node->left != NULL)
    {
        max_height = node->left->height;
    }
    if (node->right != NULL)
    {
        max_height = max_height > node->right->height ? max_height : node->right->height;
    }
    node->height = max_height + 1;
    return node->height;
}
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

/**
 * 本节点是否需要旋转
 *  返回左右子树的高度差
 */
int height_diff(Node *node)
{
    int left_height = node->left == NULL ? 0 : node->left->height;
    return left_height - (node->right == NULL ? 0 : node->right->height);
}

Node *right_rotate(Node *node, Tree *tree)
{
    Node *lk = node->left;
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
    node_height(node);
    node_height(node->parent);
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
    node_height(node);
    node_height(rk);
    return node->parent;
}

void rotate(Node *k, Tree *tree)
{
    if (height_diff(k) > 1)
    {
        if (k->left->height - (k->right == NULL ? 0 : k->right->height) > 0)
        {
            right_rotate(k, tree);
        }
        else
        {
            left_rotate(k->left, tree);
            right_rotate(k, tree);
        }
    }
    else if (height_diff(k) < -1)
    {
        if (k->right->height - (k->left == NULL ? 0 : k->left->height) > 0)
        {
            left_rotate(k, tree);
        }
        else
        {
            right_rotate(k->right, tree);
            left_rotate(k, tree);
        }
    }
}

Node *insert(Tree *tree, int key, void *value)
{
    if (tree == NULL || tree->root == NULL)
    {
        tree->root = create_node(key, value);
        return tree->root;
    }
    int height = 1;
    Node *k = tree->root;
    while (k != NULL)
    {
        if (k->key == key)
            return k;
        if (k->key < key)
        {
            if (k->right == NULL)
                break;
            k = k->right;
        }
        else
        {
            if (k->left == NULL)
                break;
            k = k->left;
        }
    }
    Node *node = create_node(key, value);
    if (k->key > key)
    {
        k->left = node;
    }
    else
    {
        k->right = node;
    }
    node->parent = k;
    while (k != NULL)
    {
        rotate(k, tree);
        node_height(k);
        k = k->parent;
    }
    return node;
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
                printf("%3d", node_queue[i]->key);
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

Node *search(Tree *tree, int key)
{
    if (tree == NULL)
        return NULL;
    if (tree->root == NULL)
        return NULL;
    Node *k = tree->root;
    while (k)
    {
        if (k->key == key)
            return k;
        if (k->key < key)
            k = k->right;
        else
            k = k->left;
    }

    return NULL;
}

/**
 * 节点前驱
 */
Node *forerunner(Node *node)
{
    Node *k = node;
    if ((k = node->left) != NULL)
    {
        while (k->right)
        {
            k = k->right;
        }
        return k;
    }
    while (k->parent != NULL && k == k->parent->left)
        k = k->parent;
    if (k != node)
        return k;
    return NULL;
}

/**
 * 节点后继
 */
Node *successor()
{
}

void delete(Tree *tree, int key)
{
    Node *node = search(tree, key);
    if (node == NULL)
        return;
    Node *k = node;
    /**
     * this is ROOT
     * root 节点需要重新变更
     */
    if (node->left == NULL || node->right == NULL)
    {
        k = (node->left == NULL) ? node->right : node->left;
        if (node->parent == NULL)
            tree->root = k;
        if (node->parent->left == node)
            node->parent->left = k;
        else if (node->parent->right == node)
            node->parent->right = k;
        if (k != NULL)
        {
            k->parent = node->parent;
            while (k->parent != NULL)
            {
                rotate(k, tree);
                node_height(k->parent);
                k = k->parent;
            }
        }
        free(node);
        return;
    }
    if (node->left->height - node->right->height > 0)
    {
        k = node->left;
        while (k->right != NULL)
            k = k->right;
    }
    else
    {
        k = node->right;
        while (k->left != NULL)
            k = k->left;
    }
    Node * successor =NULL;
    if(k->left == NULL){
       successor = k->right;   
    }else{
        successor = k->left;
    }
    if(k->parent->left == k){
        k->parent->left = successor;
    }else{
        k->parent->right = successor;
    }
    node->key = k->key;
    node->value = k->value;
    if(successor != NULL) successor ->parent = k->parent;
    Node *p = k;
    while (k->parent != NULL)
    {
        rotate(k, tree);
        node_height(k->parent);
        k = k->parent;
    }
    free(p);
}

int main(int argc, char *argv[])
{
    Tree *tree = malloc(sizeof(struct Tree));
    Node *root = insert(tree, 10, NULL);
    insert(tree, 20, NULL);
    insert(tree, 30, NULL);
    insert(tree, 40, NULL);
    insert(tree, 9, NULL);
    insert(tree, 8, NULL);
    insert(tree, 7, NULL);
    insert(tree, 6, NULL);
    print1(tree);
    delete (tree, 10);
    printf("--after delte 10\n");
    print1(tree);
    delete (tree, 9);
    printf("--after delte 9\n");
    print1(tree);
    delete (tree, 20);
    printf("--after delte 20\n");
    print1(tree);
}
