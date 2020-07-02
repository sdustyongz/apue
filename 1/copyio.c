#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFSIZE 1024

int main(int ac,char *av[]){
	int n;
	char buf[BUFFSIZE];

	while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
		if(write(STDOUT_FILENO,buf,n)!=n)
			perror("error happen");
			
	if(n<0)
		perror("error happen");
	exit(0);
}
