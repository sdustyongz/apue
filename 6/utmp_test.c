#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>

int main(int ac,char *av[]){
    struct utmp * ut;
    setutent();
    while((ut = getutent()) != NULL){
        printf("%s -  %s\n",ut->ut_line,ut->ut_name);
    }
    endutent();

    FILE * fp;
    struct utmp uu;

    if((fp = fopen(UTMP_FILE,"r")) == NULL){
        perror("open error");
        exit(1);
    }

    while((fread(&uu,sizeof(uu),1,fp)) ==1 ){
        printf("%s -  %s\n",uu.ut_line,uu.ut_name);
    }
}
