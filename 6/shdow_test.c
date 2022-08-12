#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>

int main(int ac,char *av[]){
    struct spwd * pw;
    setspent();
    while((pw = getspent()) != NULL){
        printf("%s-----%s\n",pw->sp_namp,pw->sp_pwdp);
    }
    endspent();
}
