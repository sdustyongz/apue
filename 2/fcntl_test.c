#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void get_fcl(int fd){
    int val;

    if((val = fcntl(fd,F_GETFD)) < 0){
        perror("fcntl F_GETFD fail");
        exit(1);
    }
    switch(val & O_ACCMODE){
        case O_RDONLY:
            printf("read only \n");
            break;
        case O_WRONLY:
            printf("write only \n");
            break;
        case O_RDWR:
            printf("read and write\n");
            break;
        default :
            printf("unknow \n");
            
    }

    if(val & O_APPEND)
        printf(",append ");
    if(val & O_SYNC)
        printf(",synchronous writes");
    printf("\n");

}

int main(int ac,char *av[]){
    get_fcl(STDIN_FILENO);
}


