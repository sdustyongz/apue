#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include "node.h"

void addEleInNode(Node *node, int element, Node *valueRight);
void nodeBalance(Node *node);

static Node *root = NULL;

Node *addEle(int ele)
{
    if (root == NULL)
    {
        root = (Node *)malloc(sizeof(Node));
        memset(root, 0, sizeof(Node));
        root->values[0] = ele;
        root->size = 1;
        return root;
    }
    else
    {
        Node *node = root;
        Node *parent = node;
        int i = 0;
        while (node != NULL && i < node->size)
        {
            if (node->values[i] > ele)
            {
                parent = node;
                node = node->children[i];
                i = 0;
            }
            else
            {
                i++;
            }
        }
        if (parent != NULL)
        {
            addEleInNode(parent, ele, NULL);
        }
        // if(parent != NULL){
        //     int j = 0;
        //     for(j = parent->size;  parent->values[j-1] >ele  ;j--){
        //         parent->values[j] = parent->values[j-1];
        //         parent->children[j+1] = parent->children[j];
        //     }
        //     parent->values[j] = ele;
        //     parent->size ++;

        // }
    }
}

/**
 * @brief Create a New Node object ,
 * 
 * @param num 
 * @param values 
 * @return Node* 
 */
Node *createNewNode(int value)
{

    Node *node = (Node *)malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));

    node->values[0] = value;
    node->size = 1;

    return node;
}

void addEleInNode(Node *node, int element, Node *valueRight)
{
    int j = node->size;
    // if (node->size == TREE_NODE_COUNT)
    // {
    //     j++;
    // }
    for (j; node->values[j - 1] > element && j > 0; j--)
    {
        node->values[j] = node->values[j - 1];
        node->children[j + 1] = node->children[j];
    }

    node->values[j] = element;
    node->children[j + 1] = valueRight;
    if(valueRight != NULL)
        valueRight->parent = node;
    node->size++;

    if (node->size > TREE_NODE_COUNT)
    {
        nodeBalance(node);
    }
}

/*
    
**/
void nodeBalance(Node *node)
{
    int i;
    if (node->size > TREE_NODE_COUNT)
    {
        int mid = TREE_NODE_COUNT / 2;
        int topMoveEle = node->values[mid];
        int *values = malloc(sizeof(int) * (TREE_NODE_COUNT - mid));
        Node *newNode = malloc(sizeof(Node));
        memset(newNode, 0, sizeof(Node));
        for (i = mid + 1; i <= TREE_NODE_COUNT; i++)
        {
            newNode->values[i - mid - 1] = node->values[i];
            newNode->children[i - mid - 1] = node->children[i];
            newNode->size++;

            node->values[i - 1] = 0;
            node->children[i] = NULL;
            node->size--;
        }
        node->size --;
        if (node->parent != NULL)
            addEleInNode(node->parent, topMoveEle, newNode);
        else
        {
            Node *newRoot = createNewNode(topMoveEle);
            newRoot->children[0] = node;
            newRoot->children[1] = newNode;

            node->parent = newRoot;
            newNode->parent = newRoot;
            root = newRoot;
        }
    }
}

int main(int argc, char *argv[])
{
    addEle(1);
    addEle(20);
    addEle(10);
    addEle(30);
    addEle(12);
    addEle(5);
    addEle(9);
    addEle(8);
     addEle(2);
    addEle(3);
    addEle(4);
    addEle(7);
    for (int i = 0; i < TREE_NODE_COUNT; i++)
        printf(" root is %d  ", root->values[i]);
    printf("\n");
    for (int i = 0; i < TREE_NODE_COUNT+1; i++){
        Node * node = root->children[i];
        if(node != NULL){
             for (int j = 0; j < TREE_NODE_COUNT; j++)
            printf(" root is %d    ", node->values[j]);
        }
          printf("\n");
    }
}
