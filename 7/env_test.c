#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char ** environ;

int main(int ac,char *av[]){
    printf("in env test\n");
    while(*environ != NULL)
        printf("%s\n",*environ++);
}
