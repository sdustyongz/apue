#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 2048

int main(int argc,char *argv[]){
    char line[MAXLINE];
    FILE * fpin;

    if((fpin = popen("./myuclc","r")) == NULL){
        printf("popen error \n");
        exit(1);
    }

    for( ; ; ){
        fputs("prompt> ",stdout);
        fflush(stdout);
        if(fgets(line,MAXLINE,fpin) == NULL)
            break;
        if(fputs(line,stdout) == EOF){
            printf("popen error \n");
            exit(1);
        }
    }
    if(pclose(fpin) == -1){
        printf("fputs error to pipe");
        exit(1);
    }
    putchar('\n');
    return 0;
}

