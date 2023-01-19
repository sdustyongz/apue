#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int pid;

    if(mkfifo(argv[1],S_IRWXU) != 0){
        printf("mkfifo error\n");
        exit(1);
    }
    int fd;
    if((fd = open(argv[1],O_RDWR)) < 0){
        printf("open error\n");
        perror("fork error");
        exit(1);
    }

    if((pid = fork()) < 0){
        printf("fork error\n");
        perror("fork error");
        exit(1);
    }

    if(pid == 0){
        write(fd,"1234",4);
        exit(0);
    }

    char buf[100];
    if(pid > 0){
        while(read(fd,buf,100) > 0){
            printf("%s \n",buf);
        }
    }
    
}