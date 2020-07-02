#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	printf("main pid is %d,ppid is %d\n",getpid(),getppid());
	if((pid=fork())<0){
		perror("fork faile");
	}
	if(pid>0){
		sleep(10);
		system("ps -o pid,ppid,state,tty,command");
	}else if(pid==0){
		printf("child pid is %d,ppid is %d\n",getpid(),getppid());
		exit(0);
	}
}
