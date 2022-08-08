#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int ac,char *av[]){
    struct stat buf;
    int i ;
    char * ptr ;
    for(i = 1;i < ac ;i++){
        printf("%s: ",av[i]);
        if(lstat(av[i],&buf) < 0){
            perror("stat error ");
            continue;
        }
        if(S_ISREG(buf.st_mode))
           ptr = "regular"; 
        else if(S_ISDIR(buf.st_mode))
            ptr = "directory";
        else if(S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if(S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if(S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if(S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if(S_ISSOCK(buf.st_mode))
            ptr = "sockt";
        else ptr = "UNKNOW";
        printf("%s\n",ptr);
    } 
    return 0;
}
