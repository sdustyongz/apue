#include "b_tree.h"
#include "../collection/queue.h"

BTNode * root;

BTNode * createNode(){
    BTNode * node = malloc(sizeof(BTNode));
    if(node != NULL){
        node->isLeaf = 1;
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
    while(i >= 0 && key < node->value[i]){
        i--;
    }
    if(i >=0 && key == node->value[i]) return node;
    return search(node->ptr[i+1],key);
}

void split_node(BTNode * parent ,int index){
    BTNode * child = parent->ptr[index];
    int t = KEY_NUM/2+1;
    BTNode * node  = createNode();
    node->isLeaf = child->isLeaf;
    int i = KEY_NUM-1;

    for(i = 0;i < t-1;i++){
        node->value[i] = child->value[i+t];
        child->value[i+t] = 0;
        node->ptr[i] = child->ptr[i+t];
        child->ptr[i+t] = NULL;
    }
    
    node->ptr[i] = child->ptr[i+t];
    child->ptr[i+t] = NULL;
   
    child->num = t-1;
    node->num = t-1;

    i = parent->num-1;
    int key = child->value[t-1]; 
    while(i >= 0 && key <parent->value[i]){
        parent->value[i+1] = parent->value[i];
        parent->ptr[i+2] = parent->value[i+1];
        i--;
    }
    parent->value[i+1] = key;
    parent->ptr[i+2] = node;
    parent->num++;
}

void insert_node(int key){
   if(root->num == KEY_NUM){
    BTNode * node = createNode();
    node->isLeaf = 0;
    node->ptr[0] = root;
    root = node;
    split_node(node,0);
    insert_notfull_node(root,key);
   }else{
    insert_notfull_node(root,key);
   }
}

void insert_notfull_node(BTNode * x, int key){
    int i = x->num-1;
    if(x->isLeaf !=0 ){
        while(i >=0 && key < x->value[i]){
            x->value[i+1] = x->value[i];
        }
        x->value[i+1] = key;
        x->num++;

    }else{
        while(i >= 0 && key < x->value[i]);
        BTNode * y = x->ptr[i+1];
        if(y->num == KEY_NUM){
            split_node(x,i+1);
        }
        insert_notfull_node(y,key);
    }
}

void print(){
    BTNode * p = root;
    queue * que = init_queue();
    add(que,(void *)p);
    int i = 0;
    int j = 0;
    queue * temp = init_queue();;
    while(que->size > 0){
       i = que->size;
       while(i-- > 0){ 
         BTNode * bnode = (BTNode *)offer(que);
         for(j = 0;j < bnode->num; j++){
            printf("%d ",bnode->value[i]);
            if(bnode->ptr[i] != NULL){
                add(temp,bnode->ptr[i]);
            }
         }
         add(temp,bnode->ptr[j]);
         printf("    ");
       } 
       free(que);
       que = temp;
       temp = init_queue();
       printf("\n");
    }
}

int main(int argc,char *argv[]){
   root = createThree();
   insert_node(10);
   insert_node(1);
   insert_node(5);
   insert_node(6);
   insert_node(3);
   insert_node(2);
   insert_node(4);
//    print();
return 1;
}