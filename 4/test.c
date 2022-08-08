#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac,char * av[]){
    printf("euid is %d\n",geteuid());
    if(unlink("/dev/fd/1") < 0){
        perror("error");
    }
    return 0;
}
