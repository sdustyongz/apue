#include <stdio.h>
#include <stdlib.h>

#define LEFT(i)  2*(i)
#define RIGHT(i) 2*(i)+1
#define  PARENT(i) (i)/2

struct element{
    int key;
    void * data;
};



void maxheapify(struct element * element, int i){

}