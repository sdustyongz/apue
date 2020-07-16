#include <stdlib.h>
#include <stdio.h>
#include "pr_exit.c"

int main(int ac,char *av[]){
	
	if(ac<2){
		perror("user age: cmdstr");
	}
	int status;
	if((status=system(av[1]))<0)
		perror("system error!");
	pr_exit(status);
	exit(0);
	
}
