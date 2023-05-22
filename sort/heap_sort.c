#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEFT(i)  2*(i)
#define RIGHT(i) 2*(i)+1
#define  PARENT(i) (i)/2

static int size = 0;

struct element{
    int key;
    void * data;
};



void maxheapify(struct element * elms, int i){
    int max = i;
    int left = LEFT(i);
    int right = RIGHT(i);

    if(left < size && elms[i].key < elms[left].key){
        max = LEFT(i);
    }

    if(right < size && elms[max].key < elms[right].key){
        max = RIGHT(i);
    }
    if(max != i){
        struct element   tmp ; 
        memcpy(&tmp , &elms[max], sizeof(struct element));
        elms[max] = elms[i];
        elms[i] = tmp ; 
        maxheapify(elms,max);
    }
}


void build_max_heap(struct element * elms , int siz){
    size = siz;
    int i = floor(size/2);
    while(i >= 0){
        maxheapify(elms, i);
        i--;
    } 
}


int main(int argc , char *argv[]){
    struct element els[5];
    for(int i = 0;i < 5 ;i++){
        els[i].key = i;
        els[i].data = (void *)0;
    }

    build_max_heap(els, 5);
    for(int i = 0;i < 5;i++)
        printf("%d\n",els[i].key);
}