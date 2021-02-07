#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "error.c"

int main(int ac,char*av[]){
	if(ac<2)
		err_exit(2,"parameter count wrong");
	int val;
	if((val=fcntl(atoi(av[1]),F_GETFL,0))<0)
		err_exit(2,"fcntl error");
	switch (val&O_ACCMODE){
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			err_dump("unknown access mode");
	}

	if(val&O_APPEND)
		printf(",append");
	if(val&O_NONBLOCK)
		printf(",nonblocking");
	if(val&O_SYNC)
		printf(",synchronous writes");
	printf("\n");
	exit(0);
}
