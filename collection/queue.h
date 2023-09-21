

struct queue_node {
    void * value;
    struct queue_node * next;
};
typedef struct queue_node qnode;

struct queue{
    qnode * header;
    qnode * tail;
    int size;
};

typedef struct queue queue;
queue * init_queue();
void add(queue * que,void * value);
void * offer(queue * que);