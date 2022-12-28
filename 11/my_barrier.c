#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct barrier_t {
    pthread_mutex_t mtx;

    pthread_cond_t cv;

    unsigned int n_threads;
    unsigned int count;
    unsigned int times_used;

} barrier_t;

int barrier_init(barrier_t * barrier, unsigned int num_threads){
    pthread_mutex_init(&barrier->mtx,NULL);

    pthread_cond_init(&barrier->cv,NULL);
    barrier->n_threads = num_threads;
    barrier->count = 0;
    barrier->times_used = 0;
    return 0;
}

int barrier_wait(barrier_t * barrier){
    pthread_mutex_lock(&barrier->mtx);

    barrier->count++;
    while(barrier->count < barrier->n_threads){
        pthread_cond_wait(&barrier->cv, &barrier->mtx);
    }
    
    if(++barrier->count  < barrier->n_threads){
        while(barrier->count < barrier->n_threads)
            pthread_cond_wait(&barrier->mtx,&barrier->cv);
    }else{
        
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