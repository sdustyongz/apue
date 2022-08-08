#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RWXRWXRWX S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH
int main(int ac,char * av[]){
    if(creat(av[1],RWXRWXRWX) < 0){
        perror("create error");
        exit(0);
    }
    mode_t o_umask = umask(S_IWGRP|S_IWOTH);
    if(creat(av[2],RWXRWXRWX) < 0){
        perror("create error");
        exit(0);
    }
}
