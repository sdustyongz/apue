#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"
#include "../collection/stack.h"

Node * root;
int height = 0;
int size = 0;

Node * create_node(int key, void * val, Node* parent){
    Node * node = malloc(sizeof(Node));
    node->key = key;
    node->parent = parent;
    node->value = val;
    node->right = NULL;
    node->left = NULL;
    return node;
}

Node * insert( int key, void * val){
    if(root == NULL){
        root = create_node(key,val,NULL);
        height = 1;
        size =1;
        return root;
    }
    Node * p = root,*parent = root;
    int three_height = 0;
    while(p){
        parent = p;
        if(p->key > key)
            p = p->left;
        else if(p->key == key)
            return p;
        else p = p->right;
        three_height++; 
    }
    if(height < three_height+1){
            height = three_height+1;
    }
    size ++;
    if(parent->key < key){
        parent->right = create_node(key,val, parent);
        return parent->right;
    }else{
        parent->left = create_node(key,val, parent);
        return parent->left;
    }
}

void print(){
    Node * p  =root;
    stack_t * stack  =  init_stack((int)pow(2,height));
    stack_push(stack, root);
    int i = 0;
    while(stack_length(stack)  > 0){
        i = 0;
        int st_length = stack_length(stack);
        Node ** temp = malloc(sizeof(Node *)*st_length);
        while((p = stack_pop(stack)) != NULL){
            temp[i++] = p;
        }
        i = 0;
        while(i < st_length){
            p = temp[i++];
            printf("%d \n", (int)p->value);
            if(p->left != NULL)
             stack_push(stack,p->left);
            if(p->right != NULL)
             stack_push(stack, p->right);
        }
        free(temp);
    }       

}

int main(int argc, char*argv[]){
    insert( 1, 3);
    insert(2,4);
    insert( 10 ,10);
    insert(3,5);
    print();
    printf("height is %d\n",height);
}
                
                
                
                
                
                
                
                
                
