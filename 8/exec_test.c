#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

char * env_init[]={"USER=unknow","PATH=/tmp",NULL};

int main(void){
	pid_t pid;
	if((pid=fork())<0)
		perror("fork() error");
	else if(pid==0){
		if(execle("b.out","b.out","arg1","abc",(char*)0,env_init)<0)
			perror("excle fail");
	}

	if(waitpid(pid,NULL,0)<0)
		perror("wait error");
	if((pid=fork())<0)
		perror("fork() error");
	else if(pid==0){
		if(execlp("b.out","b.out","arg1","abc",(char*)0)<0)
			perror("excle fail");
	}

	if(waitpid(pid,NULL,0)<0)
		perror("wait error");

}

