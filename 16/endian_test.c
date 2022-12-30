#include <stdio.h>
#include <stdlib.h>

int  endian_test(){
    int num = 0x01020304 ;
    char * ptr = (char *) &num;
    if(*ptr == 0x04&&ptr[1] == 0x03){
        printf("small\n");
    }else printf("big\n");

}

int  main(int argc, char *argv[]){
    endian_test();
}