#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0

struct Node
{
    int key;
    void *value;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    short color;
};
typedef struct Node Node;

struct Tree
{
    Node *root;
    int size;
};
typedef struct Tree Tree;

void insert_balance(Node *node, Tree *tree);
void rb_delete_fixup(Tree *tree, Node *node);

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
    Tree *tree = malloc(sizeof(Tree));
    memset(tree, 0, sizeof(Tree));
    return tree;
}

Node *createNode(int key, void *value)
{
    Node *node = malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    node->key = key;
    node->value = value;
    node->color = RED;
    return node;
}

Node *insert(Tree *tree, int key, void *value)
{
    Node *node = createNode(key, value);
    if (tree->root == NULL)
    {
        node->color = BLACK;
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

    Node *parent = node->parent;
    Node *left = node->left;
    node->left = left->right;
    left->right = node;
    left->parent = parent;
    node->parent = left;
    if (parent == NULL)
    {
        tree->root = left;
    }
    else
    {
        if (parent->right == node)
        {
            parent->right = left;
        }
        else
        {
            parent->left = left;
        }
    }
    return left;
}

Node *left_rotate(Node *node, Tree *tree)
{
    Node *parent = node->parent;
    Node *right = node->right;
    node->right = right->left;
    right->left = node;
    right->parent = parent;
    node->parent = right;
    if (parent == NULL)
    {
        tree->root = right;
    }else {
        if(parent->left == node){
            parent->left = right;
        }else{
            parent->right = right;
        }
    }
   return right; 
}

Node *search(Tree *tree, int key)
{
    if (tree == NULL)
        return NULL;
    Node *k = tree->root;
    while (k != NULL)
    {
        if (k->key == key)
            return k;
        if (k->key > key)
            k = k->left;
        else
            k = k->right;
    }
    return NULL;
}

void insert_balance(Node *node, Tree *tree)
{
    Node *parent = node->parent;
    if (parent == NULL)
    {
        node->color = BLACK;
        return;
    }
    if (parent->color == BLACK)
        return;
    // parent->parent 一定存在，因为root为黑色
    Node *grandfather = parent->parent;
    Node *uncle;
    if (grandfather->left == parent)
        uncle = parent->parent->right;
    else
        uncle = grandfather->left;
    if (uncle != NULL && uncle->color == RED)
    {
        parent->color = BLACK;
        parent->parent->color = RED;
        uncle->color = BLACK;
        insert_balance(grandfather, tree);
    }
    else
    {
        // 叔父节点为黑
        if (parent == grandfather->left)
        {
            if (node == parent->left)
            {
                parent->color = BLACK;
                grandfather->color = RED;
                right_rotate(parent->parent, tree);
            }
            else
            {
                left_rotate(parent, tree);
                node->color = BLACK;
                node->parent->color = RED;
                right_rotate(node->parent, tree);
            }
        }
        else
        {
            if (node == parent->right)
            {
                parent->color = BLACK;
                grandfather->color = RED;
                left_rotate(grandfather, tree);
            }
            else
            {
                right_rotate(parent, tree);
                node->color = BLACK;
                node->parent->color = RED;
                left_rotate(node->parent, tree);
            }
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
                printf("%d-%d", node_queue[i]->key, node_queue[i]->color);
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

/**
 * 后继
 */
Node *sucessor(Tree *tree, Node *node)
{
    Node *k;
    if ((k = node->right) != NULL)
    {
        while (k->left != NULL)
        {
            k = k->left;
        }
        return k;
    }
    k = node;
    while (k)
    {
        if (k->parent && k == k->parent->left)
            return k->parent;
        else
            k = k->parent;
    }
    return NULL;
}

Node *delete(Tree *tree, int key)
{
    Node *node = search(tree, key);
    if (node == NULL)
        return NULL;
    Node *x, *y;
    if (node->left == NULL || node->right == NULL)
        y = node;
    else
        y = sucessor(tree, node);
    if (y->left == NULL)
        x = y->right;
    else
        x = y->left;
    if (y == tree->root)
    {
        tree->root = x;
        x->parent = NULL;
        x->color = 0;
        return y;
    }
    else
    {
        if(x)
            x->parent = y->parent;
    }
    if (y != node)
    {
        node->key = y->key;
        node->value = y->value;
    }
    if (y->color == BLACK)
    {
        if(x){
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
         rb_delete_fixup(tree,x);
         free(y);
        }
        else{
            rb_delete_fixup(tree,y);
            if(y->parent->left == y)
                y->parent->left = y->left == NULL? y->right:y->left; 
            else  y->parent->right = y->left == NULL? y->right:y->left; 
            free(y);
        }
    }
}

int color(Node *node)
{
    if (node == NULL)
        return 0;
    return node->color;
}

void rb_delete_fixup(Tree *tree, Node *node)
{
    Node *parent ,*brother;
    while (node != tree->root && color(node) == BLACK)
    {
        parent = node->parent;
        if (node == parent->left)
        {
            brother = parent->right;
            if (color(brother) == RED)
            {
                brother->color = BLACK;
                left_rotate(parent, tree);
                parent->color = RED;
                brother = parent->right;
            }
            if (color(brother) == 0 && color(brother->left) == 0 && color(brother->right) == 0)
            {
                brother->color = RED;
                node = parent;
            }
            else
            {
                if (color(brother) == BLACK && color(brother->right) == BLACK)
                {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    right_rotate(brother, tree);
                    brother = brother->parent;
                }
                brother->color = brother->parent->color;
                brother->parent->color = BLACK;
                if(brother->right)
                    brother->right->color = BLACK;

                left_rotate( brother->parent,tree);
                node = tree->root;
            }
        }
        else
        {
            brother = parent->left;
            if(color(brother) == 1){
                brother->color = 0;
                right_rotate(parent, tree);
                brother = brother->right; 
            }
            if(color(brother->left) == BLACK && color(brother->right) == BLACK){
                brother->color = RED;
                node = parent;
            }else{
                if(color(brother->left) == BLACK){
                    brother->color = RED;
                    if(brother->left)
                         brother->left->color = BLACK;
                    left_rotate(brother,tree);
                    brother = brother->parent;
                }

                brother->color = brother->parent->color;
                brother->parent->color = BLACK;
                brother->left->color = BLACK;
                right_rotate(brother->parent, tree);
                node = tree->root;
            }
        }
    }
    node->color = BLACK;
}

int main(int argc, char *argv[])
{
    Tree *tree = createTree();
    insert(tree, 10, NULL);
    insert(tree, 5, NULL);
    insert(tree, 7, NULL);
    insert(tree, 30, NULL);
    insert(tree, 20, NULL);
    insert(tree, 40, NULL);
    print1(tree);

    delete(tree,7);
    print1(tree);
}
