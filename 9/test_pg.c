#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig){
    printf("receive sig is %d\n",sig);
}

int main(){

    pid_t pid;

    if((pid = fork()) < 0){
        perror("fork error");
        exit(1);
    }

    if(pid == 0){
        
         signal(SIGTTOU,SIG_IGN);
        setpgid(getpid(),0);
        printf("pgrpId is %d\n",tcgetpgrp(STDIN_FILENO));
        if(tcsetpgrp(STDIN_FILENO,getpid()) < 0){
            printf("error\n");

        }
        printf("pgrpId is %d\n",tcgetpgrp(STDIN_FILENO));
        printf("hello child\n");
    }else{
        printf("parent pgrpId is %d\n",tcgetpgrp(STDIN_FILENO));
        waitpid(pid,NULL,0); 
        printf("parent pgrpId is %d\n",tcgetpgrp(STDIN_FILENO));
    }
}
