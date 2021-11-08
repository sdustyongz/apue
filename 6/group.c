#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <unistd.h>

void detail_group(struct group * gp){
     printf ("group name is %s,passwd is %s,gid is %d ,user list :\n",gp->gr_name,gp->gr_passwd,gp->gr_gid);
    char * user;
    char ** gm = gp->gr_mem;
    while((user = *(gm++)) != NULL){
        printf("      %s\n",user);
        
    }
}

int main(int ac,char * av[]){
    struct group * gp ;
    while ( (gp = getgrent()) != NULL){
       detail_group(gp) ;
    }
    endgrent();
    gid_t gids[16];
    int len=0;
    if((len = getgroups(16,gids)) != -1){
        for(int i=0;i<len;i++){
            printf("gps is %d\n",gids[i]);
        }
    }
}