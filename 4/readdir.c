#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int ac,char * av[]){
	if(ac<2)
		perror("useage : path");
	int fd;
	char buf[1024];
	if((fd=open(av[1],O_RDONLY))==-1)
		perror("can not open  \n");
	int count=0;
	while((count=read(fd,buf,1023))>0){
		buf[count]='\0';
		printf("%s",buf);
	}
	printf("\n");
}
