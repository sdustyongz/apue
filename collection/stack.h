
struct stack{
    void ** base;
    void ** top;
    int size;
};

typedef struct  stack stack_t;

stack_t * init_stack(int size);
int stack_push(stack_t * stack, void * node);

void * stack_pop(stack_t * stack);
int  stack_free(stack_t * stack);
int stack_length(stack_t * stack);