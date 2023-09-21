#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


queue* init_queue(){
    queue * que =  malloc(sizeof(queue));
    que->size = 0;
    que->header = NULL;
    return que;
}

void add(queue * que, void * value){
    qnode * node = malloc(sizeof(qnode));
    node->value = value;
    node->next = NULL;
    if(que->header == NULL){
        que->tail = que->header = node;
        que->size = 1;
    }else{
        que->tail->next = node;
        que->tail = node;
        que->size++;
    }
}

void * offer(queue * que){
    if(que->header != NULL){
        qnode * node = que->header;
        void * value = node->value;
        que->header = node->next;
        que->size--;
        free(node);
        return value;
    }
    return NULL;

}

#ifdef TEST
int main(int argc,char *argv[]){
    queue * q = init_queue();
    add(q,2);
    add(q,3);
    add(q,1);
    printf("%d\n",offer(q));
    printf("%d\n",offer(q));
    printf("%d\n",offer(q));
    add(q,1);
    printf("%d\n",offer(q));
    printf("%d\n",offer(q));
return 1;
}
#endif 

