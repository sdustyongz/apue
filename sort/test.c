
#include <stdlib.h>
#include <stdio.h>

struct node{
    int value;
    int index;
};

typedef struct node Node;

int  quick_partication(Node * num, int start, int end){
    int q = end;
    int  i = start;
    Node q_node = num[q];
    while(i < q){
        if(num[i].value <= q_node.value){
            i++;
        }else{  
            num[q] = num[i];
            num[i] = num[q-1];
            q --;
        }
    }
    num[q] = q_node;
    return q;
}

void quick_sort(Node * nums, int start, int end){
    if(start >= end)return;
    int q;
    q = quick_partication(nums,start,end);
    quick_sort(nums,start,q-1);
    quick_sort(nums,q+1,end);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    Node * nodes = calloc(numsSize, sizeof(Node));
    for(int i = 0;i < numsSize; i++){
        Node node ;
        node.value = nums[i];
        node.index = i;
        nodes[i] = node;
    }
    quick_sort(nodes,0,numsSize-1);
    int k = 0;
    int e = numsSize - 1;
    while(k < e){
        if(nodes[k].value+nodes[e].value > target)
            e--;
        else if(nodes[k].value+nodes[e].value < target)
            k++;
        else break;
    }
    int * b = malloc(2*sizeof(int));
  
    if(k < e){
        b[0] = nodes[k].index;
        b[1] = nodes[e].index;
        *returnSize = 2 ;
    }else{
        b[0] = 0;
        b[1] = 0;
        *returnSize = 0 ;
    }
    return b;
}
int main(int argc, char *argv[]){
    int a[] = {3,2,3};
    int retSize;
    int * b = twoSum(a,3,6,&retSize);
    printf("%d      %d\n",b[0],b[1]);
    free(b);
}