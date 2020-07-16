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


