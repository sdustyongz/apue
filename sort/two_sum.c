#include <stdio.h>
#include <stdlib.h>

#define  DEFAULT_HASH_SIZE 16;

struct node {
    int val;
    int index;
    struct node * next;
};

typedef struct node Node;



int hash_func(int n){
    return n%13;
}
Node ** init_hash(int size){
    Node ** hash = calloc(size,sizeof(Node *));
    return hash;
}

int put(Node ** hash ,int n,int val){
    int  p = hash_func(n);
    Node * t = hash[p];
    hash[p] = malloc(sizeof(Node));
    hash[p]->index = val;
    hash[p]->val = n;
    hash[p]->next = t;
    return p;
}

Node * get(Node ** hash,int value){
    int p = hash_func(value);
    Node * gp = hash[p];
    while(gp  != NULL){
        if(gp->val == value)
            return gp;
        gp  = gp->next;
    }
    return NULL;
}

Node ** init_data(int * nums,int size){
    Node ** hash = init_hash(13);
    int i = 0;
    while(i < size){
        put(hash, nums[i], i);
        i++;
    }

    return hash;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    Node ** hash = init_data(nums, numsSize);
    int i = 0;
    int * b = malloc(2*sizeof(int));
    Node * p;
    while(i < numsSize){
        int left = target - nums[i];
        if((p = get(hash, left)) != NULL && p->index !=i ){
            *returnSize = 2;
            b[0] = i;
            b[1] = p->index;
            return b;
        }
        i++;
    }
    return NULL;
}
int main(int argc, char *argv[]){
    int a[] = {-3,4,3,90};
    int retSize;
    int * b = twoSum(a,4,0,&retSize);
    printf("%d      %d\n",b[0],b[1]);
    free(b);
}
