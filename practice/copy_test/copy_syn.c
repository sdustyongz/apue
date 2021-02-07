#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define  BUFFSIZE 2048

int main(int ac,char *av[]){
	char buff[BUFFSIZE];
	int count=0;
	while((count=read(STDIN_FILENO,buff,BUFFSIZE))>0){
		if(write(STDOUT_FILENO,buff,count)!=count)
			perror("wreite happen error");
	}
	if(count<0)
		perror("error");
	else
		fsync(STDOUT_FILENO);
	exit(0);
}
