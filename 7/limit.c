#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>

int main(int ac,char *av[]){
    #ifdef OPEN_MAX
    printf("openmax:%d\n",OPEN_MAX);
    #endif
    #ifdef _POSIX_OPEN_MAX
    printf("_POSIX_OPEN_MAX:%d\n",_POSIX_OPEN_MAX);
    #endif
    #ifdef _SC_OPEN_MAX
     printf("_SC_OPEN_MAX:%ld\n",sysconf(_SC_OPEN_MAX));
     #endif
     struct rlimit rl;
     getrlimit(RLIMIT_NOFILE,&rl);
     printf("cur:%ld,max:%ld\n",rl.rlim_cur,rl.rlim_max);
     
}
