#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct barrier_t {
    pthread_mutex_t mtx;

    pthread_cond_t cv;

    unsigned int n_threads;
    unsigned int count;
    unsigned int times_used;

    short int full_flag;

} barrier_t;

int barrier_init(barrier_t * barrier, unsigned int num_threads){
    pthread_mutex_init(&barrier->mtx,NULL);

    pthread_cond_init(&barrier->cv,NULL);
    barrier->n_threads = num_threads;
    barrier->count = 0;
    barrier->times_used = 0;
    barrier->full_flag = 0;
    return 0;
}

int barrier_wait(barrier_t * barrier){
    pthread_mutex_lock(&barrier->mtx);
    while(barrier->full_flag)
        pthread_cond_wait(&barrier->cv, &barrier->mtx);
    barrier->count++;
//    printf("barrier_count: %d\n",barrier->count);
    if(barrier->count == barrier->n_threads){
        barrier->full_flag  = 1;
        pthread_cond_broadcast(&barrier->cv);
    }
    while(!barrier->full_flag ){
        pthread_cond_wait(&barrier->cv, &barrier->mtx);
    }
    
    //if(barrier->count == barrier->n_threads){
    //    barrier->full_flag  = 0;
    //    pthread_cond_broadcast(&barrier->cv);
   // }

    if(--barrier->count  == 0){
        barrier->full_flag =0;
        pthread_cond_broadcast(&barrier->cv);
    } 
    
    pthread_mutex_unlock(&barrier->mtx);
    return 0;
}

int barrier_destroy(barrier_t * barrier){
    pthread_cond_destroy(&barrier->cv);
    pthread_mutex_destroy(&barrier->mtx);
    barrier->count = 0;
    barrier->n_threads = 0;
}