#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>

int main(int ac , char * av[]){
    struct passwd * pw;
    if((pw = getpwuid(0)) ==NULL){
        printf("get root error:\n");
        return 1;
    }

    printf("name is %s,pw is %s ,dir is %s , shell file is %s\n",pw->pw_name,pw->pw_passwd,pw->pw_dir,pw->pw_shell);

    while((pw = getpwent()) != NULL){
          printf("name is %s,pw is %s ,dir is %s , shell file is %s\n",pw->pw_name,pw->pw_passwd,pw->pw_dir,pw->pw_shell);
    }
    endpwent();

    struct spwd * shdow;
    while((shdow = getspent()) != NULL){
        printf("sp_name is %s,sp_pwdp is %s\n",shdow->sp_namp,shdow->sp_pwdp);
    }
}
