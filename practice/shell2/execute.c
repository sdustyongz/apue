#include<stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int execute(char *argv[]){
	int child_id=-1;
	int child_info=-1;
	if((child_id=fork())==-1){
		perror("fork");

	}else if(child_id==0){
		signal(SIGINT,SIG_DFL);
		signal(SIGQUIT,SIG_DFL);
		execvp(argv[0],argv);
		exit(-1);
	}else {
		if(wait(&child_info)==-1)
			perror("wait");
		return child_info;
	}
}
