#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void pr_process(char * name){
	printf("%s  pid:%d,ppid:%d,pgid:%d,sid:%d,grrp:%d\n",name,getpid(),getppid(),getpgid(getpid()),getsid(getpid()),tcgetpgrp(STDIN_FILENO));
}

void handler(int sig){
    printf("pid is %d,receive %d sig\n",getpid(),sig);
}

int main(int argc,char *argv[]){
	pid_t pid ;

	pid_t fpgid = tcgetpgrp(STDIN_FILENO);
	if((pid = fork()) < 0){
		perror("fork error");
		exit(1);
	}

	if(pid == 0){
		signal(SIGTTOU,handler);
		setpgid(getpid(),getpid());
        if((pid = fork()) <0 ){
            perror("fork2 失败");
            exit(127);
        }
        if(pid  == 0){
		    signal(SIGTTOU,handler);
            sleep(3);
            exit(0);
        }
		pr_process("child before set:");
		if(tcsetpgrp(STDIN_FILENO,getpid()) == -1){
			printf("set error\n");
			exit(2);
		}	
		pr_process("child after set");
		exit(1);
		
	}

	pr_process("parent1");
    waitpid(pid,NULL,0);	
	pr_process("parent2");
	char buf[100];
//    signal(SIGTTIN,handler);
	if(read(STDIN_FILENO,buf,100) < 0){
		perror("read error");
		printf("error\n");
		exit(127);
	}
	printf("sucess\n");
	return 0;
}
