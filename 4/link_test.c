#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int ac,char *av[]){
    if(ac <2){
        printf("useage error:\n");
        exit(1);
    }

    if(link(av[1],av[2]) < 0){
        perror("link error ");
        exit(2);
    }

    struct stat buf1;
    struct stat buf2;

    if(stat(av[1],&buf1) <0 ){
        printf("stat error\n");
        exit(3);
    }   

    if(stat(av[1],&buf2) <0 ){
        printf("stat error\n");
        exit(3);
    }   

    printf("buf1 is %d, buf2 is %d\n",buf1.st_ino,buf2.st_ino);

    
    return 1;
}


