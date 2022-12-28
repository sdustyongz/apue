#include <fcntl.h>
#include <sys/mman.h>
#include "tell_wait.c"

#define  NLOOPS 1000
#define SIZE sizeof(long)

static int update(long * ptr){
    return (*ptr)++;
}

int main(int argc, char *argv[]){
    int fd, i, counter;
    pid_t pid;
    void * area;

    if((fd = open("/dev/zero",O_RDWR)) < 0){
        printf("open error\n");
        return 1;
    }
    if((area = mmap(0,SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0)) == MAP_FAILED){
        printf("mmap error \n");
        return 1;
    }

    close(fd);
    tell_wait();

    if((pid = fork()) < 0){
        return 1;
    }else if(pid > 0){
        for(i = 0; i < NLOOPS; i+=2){
            if((counter = update((long *) area)) != i){
                printf("parent: expected %d, got %d\n",i,counter);
            }
            tell_child(pid);
            wait_child();
        }
    }else{
        for(i = 1; i < NLOOPS; i+=2){
            wait_parent();
            if((counter = update((long *) area)) != i){
                printf("parent: expected %d, got %d\n",i,counter);
            }
            tell_parent(getppid());
        }
    }
    return 0;
}