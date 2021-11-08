#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

int main(int ac,char *av[]){
    char ** env = environ;
    char * kv;
    while( (kv=*(env++)) != NULL){
        printf("%s\n",kv);
    }
}