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

/**
 * 继任者节点
*/
Node * successor(Node * node){
    if(node == NULL) return NULL;
    Node * k;
    if((k = node->right) != NULL)  {
        while(k->left != NULL) k = k->left;
        return  k;
    }
    if(node == node->parent->left) return node->parent;
    k =node;
    while(k->parent != NULL && k == k->parent->right)
        k = k->parent;
    if(k != NULL && k->parent != NULL) return k->parent;
    return NULL;
}


void print1(){
    Node * empty_node = malloc(sizeof(Node));
    memset(empty_node,0,sizeof(Node));
    Node * p  =root;
    int height = tree_height(root);
    int level = 0;
    int level_num = pow(2,level); 
    Node ** node_queue = malloc(sizeof(Node *)*level_num); 
    int first_space = (pow(2,height-1)*3 - 1)/2;
    int  i ;
    node_queue[0] = root;
    while(level < height){
       for(i = 0 ;i < first_space;i++) 
            printf("   ");
        int distance = pow(2,(height - level -1))+1;
        for(i = 0;i < level_num; i++){
            if(node_queue[i] != empty_node) 
                printf("%3d", node_queue[i]->key);
            else printf("   ");
            for(int j = 0 ;j < distance; j++)
                printf("   ");
        }
        level ++;
        Node ** temp_queue = malloc(sizeof(Node *)*pow(2,level));
        for(i = 0;i < level_num; i++){
            temp_queue[2*i] = node_queue[i]->left == NULL?empty_node:node_queue[i]->left;
            temp_queue[2*i+1] = node_queue[i]->right == NULL?empty_node:node_queue[i]->right;
        }
        level_num = pow(2,level);
        first_space-=2;
        free(node_queue);
        node_queue = temp_queue;  
        printf("\n");
    }   
    free(empty_node);
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

Node * search(int key){
    Node * k = root;
    while(k != NULL){
        if(k->key == key) return k;
        if(k->key > key) k = k->left;
        if(k->key < key) k = k->right;
    }
    return NULL;
}

int delete(int key){
    Node * node = search(key);
    if(node == NULL) return -1;
    Node * y,*x; 
    if(node->left == NULL || node->right == NULL)
        y = node;
    else {
        y = successor(node);
    }
    if(y->left != NULL)
        x = y->left;
    else x = y->right;
    node->key = y->key;
    node->value = y->value;
    if(y->parent == NULL) root =x;
    if(y->parent ->left == y)
        y->parent->left  =x;
    else y->parent->right =x;
    if(x != NULL)
        x->parent = y->parent;
    free(y);
}

int main(int argc, char*argv[]){
    insert( 4, (void*)3);
    insert(2,(void *)4);
    insert( 10 ,(void*)10);
    insert(3,(void *)5);
    insert(1,(void *)8);
    print1();
    Node* x = successor(root);
    printf("%d's successor is %d\n",root->key, x->key);
    x = successor(x);
    //printf("height is %d\n",tree_height(root));
    delete(4);
    print1();
}
                
                
                
                
                
                
                
                
                
