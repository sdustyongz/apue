#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int golobal_var = 6;
char  buf[]="wreite to stdout\n";

int main(int ac,char * av[]){
    int var = 88;
    pid_t pid;
    if(write(STDOUT_FILENO,buf,sizeof(buf)-1) != (sizeof(buf)-1)){
        printf("wreite error\n");
    }
    printf("before fork()\n");
    if((pid = fork()) < 0){
        printf(" fork error\n");
        exit(1);
    }else if(pid == 0){
        golobal_var++;
        var ++;
    }else{
        sleep(2);
    }

    printf("pid = %ld, global is %d, var is %d\n",getpid(),golobal_var,var);
    return 1;
}