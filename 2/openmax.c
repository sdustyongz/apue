#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

extern int errno;

void pr_sysconf(char * msg,int name){
    long val;
    fputs(msg,stdout);
    errno = 0;
    if((val = sysconf(name)) < 0){
        if(errno !=0 ){
             if(errno == EINVAL)
                fputs("not supported\n",stdout);
             else
                perror("sysconf error");
        }else {
            fputs("(no limit)\n",stdout);
        }
    }else{
        printf("%ld \n",val);
    }

}

void pr_pathconf(char * msg, char * path,int name){
    long val;

    fputs(msg,stdout);
    errno = 0;
    if((val = pathconf(path,name)) < 0){
        if(errno != 0)
            if(errno == EINVAL)
                fputs(" (not supported)\n",stdout);
            else 
                perror("path conf error,xxxxxpath ");
        else 
                fputs(" (not limit) \n",stdout);
    }else
        printf(" %ld\n",val);
}

int main(int ac,char *av[]){
    #ifdef OPEN_MAX 
        printf("open MAX defined is %ld\n",OPEN_MAX);
    #endif
    #ifdef _SC_OPEN_MAX
        pr_sysconf("_SC_OPEN_MAX",_SC_OPEN_MAX);
    #endif
    
    #ifdef PATH_MAX 
        printf(" path max defined is %ld\n",PATH_MAX);
    #endif
    #ifdef _SC_PATH_MAX 
        pr_pathconf("_SC_PATH_MAX",av[1],_SC_PATH_MAX);
    #endif
    #ifdef _POSIX_OPEN_MAX
        printf("_POSIX_OPEN_MAX %ld\n",_POSIX_OPEN_MAX);

    #endif

    #ifdef CLK_TCK
        printf(" CLK_TCK is %ld\n",CLK_TCK);
    #endif 
    #ifdef _SC_CLK_TCK 
        pr_sysconf("_SC_CLK_TCK ",_SC_CLK_TCK);
    #endif

    printf("CLOCK_PER_SEC is %ld\n",CLOCKS_PER_SEC);
}


