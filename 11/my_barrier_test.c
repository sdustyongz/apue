#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "my_barrier.c"

#define THREAD_COUNT 4 

barrier_t mybarrier;

void * threadFn(void * id_ptr){
    int  tid =  * (int *) id_ptr;
    int wait_sec = 1 + rand() % 5;
    printf("thread %d wait for %d second\n",tid,wait_sec);
    sleep(wait_sec);

    printf("thread %d ready\n",tid);

    barrier_wait(&mybarrier);
    
    printf("thread %d going \n",tid);
    return NULL;
}

int main(int argc, char * argv[]){
    int i;
    pthread_t tids[THREAD_COUNT];
    int shot_ids[THREAD_COUNT];

    barrier_init(&mybarrier,THREAD_COUNT+1);

    for (i = 0; i < THREAD_COUNT; i++){
        shot_ids[i] = i;
        pthread_create(&tids[i],NULL,threadFn,&shot_ids[i]);
    }
    printf("main is ready \n");
    barrier_wait(&mybarrier);
    
    for(i = 0; i < THREAD_COUNT; i++){
        pthread_join(tids[i],NULL);
    }
     for (i = 0; i < THREAD_COUNT; i++){
        shot_ids[i] = i;
        pthread_create(&tids[i],NULL,threadFn,&shot_ids[i]);
    }
    printf("main is ready \n");
    barrier_wait(&mybarrier);
    
    for(i = 0; i < THREAD_COUNT; i++){
        pthread_join(tids[i],NULL);
    }
    

    barrier_destroy(&mybarrier);
}