#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"
#include "../collection/stack.h"

Node * root;
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
        size =1;
        return root;
    }
    Node * p = root,*parent = root;
    while(p){
        parent = p;
        if(p->key > key)
            p = p->left;
        else if(p->key == key)
            return p;
        else p = p->right;
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

int tree_height(Node * root){
   if(root == NULL){
        return 0;
   } 
   int left_height = tree_height(root->left);
   int right_height = tree_height(root->right);
   if(left_height > right_height){
        return left_height+1;
   }
   return right_height +1;
}
void print(){
    Node * p  =root;
    int height = tree_height(root);
    stack_t * stack  =  init_stack((int)pow(2,height));
    stack_push(stack, root);
    int i = 0;
    int first_space = (pow(2,height-1)*3 - 1)/2;
    while(stack_length(stack)  > 0){
        i = 0;
        while(i++ < first_space){
            printf("   ");
        }
        i = 0;
        int st_length = stack_length(stack);
        Node ** temp = malloc(sizeof(Node *)*st_length);
        while((p = stack_pop(stack)) != NULL){
            temp[i++] = p;
            printf("%3d   ",p->key);
        }
        i = st_length;
        while(i > 0){
            p = temp[--i];
            //printf("%d \n", (int)p->value);
            if(p->right != NULL)
             stack_push(stack, p->right);
            if(p->left != NULL)
             stack_push(stack,p->left);
        }
        printf("\n");
        first_space = first_space -2;
        free(temp);
    }       

}

int main(int argc, char*argv[]){
    insert( 4, 3);
    insert(2,4);
    insert( 10 ,10);
    insert(3,5);
    print();
    //printf("height is %d\n",tree_height(root));
}
                
                
                
                
                
                
                
                
                
