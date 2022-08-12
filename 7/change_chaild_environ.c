#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac,char *av[]){
    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork error");
        exit(0);
    }

    if(pid == 0){
        char * child_environ[2];
        child_environ[0] = "a=b";
        child_environ[1] = NULL;

        if(execle(av[1],av[1],NULL,child_environ) == -1){
            perror("execle error");
            exit(0);
        }
        exit(0); 
    }
    int tm;
    waitpid(pid,&tm,0);
    return 0;


}
