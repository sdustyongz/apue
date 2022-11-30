#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

 sigset_t mask;
 int quitflag;
 pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

void *  thr_fn(){
    int signo;

    for( ; ; ){
        int err = sigwait(&mask,&signo);
        if(err != 0 ){
            perror("happen error");
            break;
        }
        switch (signo)
        {
            case SIGINT:
                printf("receive SIGINt\n");
                break;
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quitflag = 1;
                pthread_mutex_unlock(&lock);
                pthread_cond_broadcast(&waitloc);
                printf("receive SIGQUIT\n");
                return NULL;
            default:
                break;
        }
    }
    return NULL;
}


int main(int argc,char * argv[]){
    pthread_t tid;
   
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGQUIT);
    sigset_t oldmask;
    pthread_sigmask(SIG_SETMASK,&mask,&oldmask);

    if(pthread_create(&tid,NULL,thr_fn,(void *)NULL) != 0){
        perror("pthread create error");
        return 1;
    }
    pthread_mutex_lock(&lock);
    while(quitflag == 0)
        pthread_cond_wait(&waitloc,&lock);
    pthread_mutex_unlock(&lock);

    sigprocmask(SIG_SETMASK,&oldmask,NULL);
    return 0;
}