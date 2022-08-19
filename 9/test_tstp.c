#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc,char *argv[]){
    kill(getpid(),SIGTSTP);
    printf("hello every one \n");
}

