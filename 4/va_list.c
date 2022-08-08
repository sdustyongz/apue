#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int print_test(char * buf,...){
    va_list list;
    va_start(list,buf);
    
    int  tmp;

    while((tmp = va_arg(list,int)) > 0){

        printf("%d\n",tmp);
    }
    va_end(list);
}


int test_valist(int n,int a,int b){
    char * p = &n;
    int size = sizeof(n);
    printf("%d\n",size);
    char * np = p+size;
    int * ap =  (int *)np;
    printf("%x\n",&ap);   
}

int main(int ac,char *av[]){
    test_valist(1,100,23);
    return 0;
}
