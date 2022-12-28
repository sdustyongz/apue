#include <stdio.h>
#include <signal.h>
#include  <stdlib.h>
#include <errno.h>
#include <unistd.h>


static sigset_t newmask, oldmask, zeromask;
static volatile  sig_atomic_t sigflag;

void  sig_handler (int signo){
    sigflag = 1;
}

int tell_wait(){
    if(signal(SIGUSR1,sig_handler) == SIG_ERR){
        printf("signal (SIGUSR1) error\n");
        exit(1);
    }
    if(signal(SIGUSR2,sig_handler) == SIG_ERR){
        printf("signal (SIGUSR2) error\n");
        exit(1);
    }

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask,SIGUSR1);
    sigaddset(&newmask,SIGUSR2);
    sigprocmask(SIG_BLOCK,&newmask,&oldmask);    
}


int  wait_sig(){
    while(sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0){
        printf("sigprocmask error\n");
        return -1;
    }
    return 0;
}


int wait_parent(){
    return wait_sig();
}

int wait_child(){
    return wait_sig();
}


int tell_parent(pid_t pid){
    kill(pid,SIGUSR2);
}

int tell_child(pid_t child_pid){
    kill(child_pid,SIGUSR1);
}

