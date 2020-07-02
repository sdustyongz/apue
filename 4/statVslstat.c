#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int ac,char * av[]){
	int fd;
	if(ac<2)
		perror("use age : filepath");
	if((fd=open(av[1],O_RDWR|O_CREAT))==-1)
		perror("can not open");
	if(symlink(av[1],av[2])==-1)
		perror("can not create sym link");
	struct stat sta;
	stat(av[1],&sta);
	printf("info_t:%ld,st_mode:%ld\n",sta.st_ino,sta.st_mode);
	struct stat nsta;
	lstat(av[2],&nsta);
	printf("info_t:%ld,st_mode:%ld\n",nsta.st_ino,nsta.st_mode);

}
