#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define  BUFFSIZE 8192 

int main(int ac,char *av[]){
	char buff[BUFFSIZE];
	int fd=open("/home/22.txt",O_WRONLY|O_SYNC|O_CREAT);
	//int fd=STDOUT_FILENO;
	int count=0;
	while((count=read(STDIN_FILENO,buff,BUFFSIZE))>0){
		if(write(fd,buff,count)!=count)
			perror("wreite happen error");
	}
	if(count<0)
		perror("error");
	exit(0);
}
