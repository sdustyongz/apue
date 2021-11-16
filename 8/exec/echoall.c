#include <stdio.h>
#include <stdlib.h>

int main(int ac ,char *av[]){
    int i = 0;
    char **ptr;
    extern char **environ;

    for (i = 0; i< ac; i++)
        printf("argv[%d]:%s\n",i,av[i]);
    // for (ptr = environ; *ptr != NULL; ptr++)
    //     printf("%s\n",*ptr);
}