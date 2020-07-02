#include <stdio.h>
#include <sys/wait.h>

void pr_exit(int status){
	if(WIFEXITED(status))
		printf("正常退出,退出状态为:%d\n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("异常退出，信号编号=%d%s\n",WTERMSIG(status),
		#ifdef WCOREDUMP
			WCOREDUMP(status)?"core file generated":""	
		);
		#else
		    "");
		#endif
	else if(WIFSTOPPED(status))
		printf("子进程停止，信号编号=%d\n",WSTOPSIG(status));
}


int main(int ac,char * av[]){
	pid_t pid;
	int status;
	if((pid=fork())<0)
		perror("fork error");
	else if(pid==0){
		exit(7);
	}
	if(wait(&status)!=pid)
		perror("wait error");
	pr_exit(status);
   if((pid=fork())<0)
		perror("fork error");
	else if(pid==0){
		abort();
	}
	if(wait(&status)!=pid)
		perror("wait error");
	pr_exit(status);

}
