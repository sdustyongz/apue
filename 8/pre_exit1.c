#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


void pr_exit(int status){
	if(WIFEXITED(status))
		printf("normal termination ,exit status=%d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination ,signal number=%d%s\n",WTERMSIG(status),
	#ifdef WCOREDUMP
		WCOREDUMP(status) ?"(core file generated)" :"");
	#else
	   "");
	#endif
	else if(WIFSTOPPED(status))
		printf("child stopped,signal number =%d\n",WSTOPSIG(status));
	
}

int main(int ac,char *av[]){
	int pid;
	if((pid=fork())<0)
		perror("error");
	else if(pid==0){
		abort();
	}
	int stat;
	wait(&stat);
	pr_exit(stat);
}

