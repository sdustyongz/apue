#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    long  key;
    void * value;
    struct node * left;
    struct node * right;
    struct node * parent;
    /**
     * 以本节点为根的树的高度，默认为1
    */
    int height;
};

typedef struct node  Node;


Node * create_node(int key ,void * value){
    Node * node = malloc(sizeof(Node));
    memset(node,0,sizeof(Node));
    node->key =key;
    node->value = value;
    node -> height =1;
    return node;
}

int node_height(Node * node){
    if(node == NULL) return 0;
    int max_height = 1;
    if(node->left != NULL ){
        max_height = node->left->height;
    }
    if(node->right != NULL){
        max_height = max_height > node->right->height?max_height:node->right->height;
    }
    node->height = max_height+1;
    return node->height;
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
 * 本节点是否需要旋转
 *  返回左右子树的高度差 
*/
int height_diff(Node * node){
    int left_height = node->left == NULL? 0 :node->left->height;
    return left_height - (node->right == NULL ? 0:node->right->height);
}

Node * right_rotate(Node * node){
    
    node->left->parent = node->parent;
    node->left = node->left->right;
    if(node->left != NULL)
        node->left->parent = node;
    node->parent = node->left;
    node_height(node);
    node_height(node->parent);
    return node->parent;
}

Node * left_rotate(Node * node){
    node->right->parent = node->parent;
    node->right = node->right->left;
    if(node->right != NULL)
        node->right->parent = node;
    node->parent = node->right;
    node_height(node);
    node_height(node->parent);
    return node->parent;
}

void rotate(Node * k, Node * inserted_node){
     if(height_diff(k) > 1){
        if(inserted_node->parent->left == inserted_node){
            right_rotate(k);
        }else{
            left_rotate(k->left);
            right_rotate(k);
        }
     }else if(height_diff(k) < -1){
        if(inserted_node->parent->right == inserted_node){
            left_rotate(k);
        }else{
            right_rotate(k->right);
            left_rotate(k);
        }        

     }     
 
}



Node * insert(Node *root, int key,void * value){
    if(root == NULL){
       root = create_node(key,value);
       return root; 
    }
    int height = 1;
    Node * k;
    while((k = root) != NULL){
        if(k->key == key)
            return k;
        if(k->key < key){
            if(k->right == NULL)
                break;
            k = k->right;
        }else{
            if(k->left == NULL)
                break;
            k = k->left;
        }
    }
    Node * node =create_node(key,value);
    if(k->key > key){
        k->left = node;
    }else{
        k->right = node;
    }
    node->parent = k;
    while(k != NULL){
        rotate(k,node);
        node_height(k);
        k = k->parent;
    }
    return node;
}   
void print1(Node * root){
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

int main(int argc, char *argv[]){
    Node * root = insert(NULL,10,NULL);
    insert(root,20,NULL);
    insert(root,1,NULL);
    insert(root,2,NULL);
    insert(root,3,NULL);
    print1(root);
}

