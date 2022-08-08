#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int ac,char *av[]){
    struct stat statbuf;
    int i,fd;
    struct timespec times[2];

    for(i = 1;i < ac;i++){
        if(stat(av[i],&statbuf) < 0){
            perror(" stat error ");
            continue; 
        }
        if((fd = open(av[i],O_RDWR|O_TRUNC)) < 0){
            perror("open error");
            continue;
        }
        
        times[0] = statbuf.st_atim;
        times[1] = statbuf.st_mtim;

       if(futimens(fd,times) < 0 )
          perror("futimens error"); 
       close(fd); 
    }

    return 0;
}
