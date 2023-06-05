#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack_t * init_stack(int size){
    stack_t * st = malloc(sizeof(stack_t));
    memset(st,0,sizeof(stack_t));
    st->base = (void **)malloc(sizeof(void *)*size);
    st->top = st->base;
    st->size = size;
    return st;
}

int stack_push(stack_t * stack, void * node){
    if(stack->top - stack->base  >= stack->size){
        return -1;
    }
    *stack->top++ = node;
    return 0;
}

void * stack_pop(stack_t * stack){
    if(stack->top - stack->base  <= 0)
        return NULL;
    return *--stack->top;
}

int  stack_free(stack_t * stack){
    free(stack->base);
    free(stack);
    return 0;
}

int stack_length(stack_t * st){
    return st->top - st->base;
}