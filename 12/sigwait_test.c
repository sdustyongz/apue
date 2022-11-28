#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

 sigset_t mask;

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
                printf("receive SIGQUIT\n");
                break;
            default:
                break;
        }
    }
}


int main(int argc,char * argv[]){
    pthread_t tid;
   
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGQUIT);
    sigset_t oldmask;
    pthread_sigmask(SIG_BLOCK,&mask,&oldmask);

    if(pthread_create(&tid,NULL,thr_fn,(void *)NULL) != 0){
        perror("pthread create error");
        return 1;
    }

    pause();
    return 0;
}