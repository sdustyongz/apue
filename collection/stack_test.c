#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char *argv[]){
    stack_t * st = init_stack(10);
    stack_push(st,(void *)10);
    stack_push(st,(void *)9);
    stack_push(st,(void *)8);
    printf("%d \n",(int)stack_pop(st));
    printf("%d \n",(int)stack_pop(st));
    printf("%d \n",(int)stack_pop(st));
    printf("%d \n",(int)stack_pop(st));
    stack_free(st);
}