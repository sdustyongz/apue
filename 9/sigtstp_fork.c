#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "pr_process.c"

void handler(int sig){
    printf("hello sig,pid=%d\n",getpid());
}

int main(int ac,char*av[]){
	int pid;
	if((pid=fork())<0){
		perror("error");
		exit(1);
	}

	if(pid==0){
        signal(SIGHUP,handler);
		print_process("child");
        kill(getpid(),SIGTSTP);
		print_process("child");
        
		char buf[200];
		int count=0;
		while((count=read(STDIN_FILENO,buf,200))>0){
			buf[199]='\0';
			printf("%s\n",buf);
		}
		if(count==-1){
			perror("ssss");	
		}
	}else {
		print_process("parent");
//        sleep(2);
		exit(0);
	}
}

