#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define DEF_PAGER "/bin/more"
#define MAXLINE 2048 

int main(int argc, char *argv[]){
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    if(argc != 2){
        printf("userage a.out <pathname>");
        exit(1);
    }

    if((fp = fopen(argv[1],"r")) == NULL){
        printf("cant open %s\n",argv[1]);
        exit(1);
    }

    if(pipe(fd) < 0){
        printf("pipe error\n");
        exit(1);
    }

    if((pid = fork()) < 0){
        printf("fork error \n");
        exit(1);
    }else if(pid > 0){
        close(fd[0]);

        while(fgets(line,MAXLINE,fp) != NULL){
            n = strlen(line);
            if(write(fd[1],line,n) != n){
                printf("warning write error\n");
            }
        }
        close(fd[1]);
        if(waitpid(pid,NULL,0) < 0){
            printf("waitpid error\n");
            exit(1);
        }
        exit(0);
    }
    if(pid == 0){

        close(fd[1]);
        if(fd[0] != STDIN_FILENO){
            if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO){
                printf("dup2 error at stdin\n");
                exit(1);
            }
            close(fd[0]);
        }

        if((pager = getenv("PAGER")) == NULL)
            pager = DEF_PAGER;
        if((argv0 = strrchr(pager,'/')) != NULL)
            argv0++;
        else 
            argv0 = pager;
        
        if(execl(pager,argv0,(char*)0) < 0){
            printf("execl pager error\n");
            exit(1);
        }
    }
    return 0;
}
