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
void insert_notfull_node(BTNode * x, int key);

struct node_position{
    BTNode * pr;
    int index;
};
typedef struct node_position Np;


Np * search(BTNode * node ,int key){
    int i = node->num-1;
    while(i >= 0 && key < node->value[i]){
        i--;
    }
    if(i >=0 && key == node->value[i]){
        Np * np = malloc(sizeof(Np));
        np->pr = node;
        np->index = i;
        return np;
    } 
    if(node->isLeaf){
        return NULL;
    }
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
        parent->ptr[i+2] = parent->ptr[i+1];
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
            i --;
        }
        x->value[i+1] = key;
        x->num++;

    }else{
        while(i >= 0 && key < x->value[i])
            i--;
        BTNode * y = x->ptr[i+1];
        if(y->num == KEY_NUM){
            split_node(x,i+1);
            y  = x;
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
            printf("%d ",bnode->value[j]);
            if(bnode->ptr[j] != NULL){
                add(temp,(void*)bnode->ptr[j]);
            }
         }
         if(bnode->ptr[j] != NULL)
            add(temp,bnode->ptr[j]);
         printf("    ");
       } 
       free(que);
       que = temp;
       temp = init_queue();
       printf("\n");
    }
    free(que);
    free(temp);
}

BTNode merge_brother_node(BTNode * parent,int leftIndex ,int rightIndex){
    BTNode * lChild = parent->ptr[leftIndex];
    BTNode * rChild = parent->ptr[rightIndex];
    int i = leftIndex, j = lChild->num;
    int value = parent->value[leftIndex];
    //int ptr  = parent->ptr[leftIndex];
    while(i < parent->num-1){
        parent->value[i] = parent->value[i+1];
        parent->ptr[i+1] = parent->ptr[i+2];
    }
    i = 0;
    lChild[j++] = value;  
    while(i < rchild->num){
        lChild->value[j] = rChild->value[i];
        lChild->ptr[j] = rChild->ptr[i];
        i++;j++;
    }
    lChild->ptr[j] = rChild->ptr[lChild->num];
}

void delete_check_child(BTNode * node,int index){
    int t = KEY_NUM/2+1;
    int brothers[2];
    if(index == 0) {
        brothers[0] = 1;
        brothers[1] = -1;
    }else if(index == node->num + 1){
        brothers[0] = node->num;
        brothers[1] = -1;
    }else{
        brothers[0] = index;
        brothers[1] = index+1; 
    }
    
    if(node->prt[index]->num == t-1){
        if(brothers[0] != -1 && node->ptr[brothers[0]]->num >=t){  

        }else if(brothers[1] != -1 && node->ptr[brothers[1]]->num >=t) {

        }else{

            merge_brother_node(node,brothers);
        }
    }
}

void delete_node(int key){
    BTNode * pr = root;
    int i = pr->num - 1;
    while(i >= 0 && pr->value[i] > key ){
        i--;
    }
    if(i < 0){
            
    }else if(key == pr->value[i]){
        if(pr->isLeaf){
            delete_on_node(pr,i);
        }else{
            if(pr->ptr[i]->num > t-1){

            }else if(pr->ptr[i+1]->num > t-1){

            }else{

            }
        }

    }else{
        
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
   insert_node(20);
   insert_node(7);
   insert_node(30);
   insert_node(8);
   insert_node(9);
   insert_node(50);
   insert_node(40);
   insert_node(60);
   print();
   printf("\n");
   insert_node(70);
   print();

   Np * np =search(root,60);
   if(np != NULL){
    printf("%d\n",np->index);
   }
   np =search(root,100);
   if(np != NULL){
    printf("%d\n",np->index);
   }else{
    printf("cannotfonud\n");
   }
return 1;
}