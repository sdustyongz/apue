#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int ac,char *av[]){
    pid_t pid;

    if((pid = fork()) < 0){
        printf("fork error\n");
        return 1;
    }else if(pid == 0){
        if(execl("./echoall","ecall123","hello","world",(char *)0) < 0){
            printf("execl error\n");
            return 2;
        }
        
    }
    if(waitpid(pid,NULL,0) < 0){
        printf("waitpid error\n");
        return 3;
    }
    
    if((pid = fork()) < 0){
        printf("fork error\n");
        return 1;
    }else if(pid == 0){
        if(execlp("./pwd.sh","ecall12","hello1","world1",(char *)0) < 0){
            printf("execl error\n");
            return 2;
        }
        
    }
    
}