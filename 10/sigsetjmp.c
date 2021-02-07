#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include "pr_mask.c"

//static sigjmp_buf jmpbuf;
static jmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

void sig_usr1(int signo){
	time_t starttime;
	if(canjump==0)
		return;
	pr_mask("starting sig_usr1:");
	alarm(3);
	starttime=time(NULL);
	for( ; ;)
		if(time(NULL)>starttime+5)
			break;
	pr_mask("finishing sig_usr1:");
	canjump=0;
	//siglongjmp(jmpbuf,1);
	longjmp(jmpbuf,1);
}

void sig_alarm(int signo){
	pr_mask("in sig_alrm:");
}

int main(){
	if(signal(SIGUSR1,sig_usr1)==SIG_ERR)
		perror("signal SIGUSR1 error");
	if(signal(SIGALRM,sig_alarm)==SIG_ERR)
		perror("signal SIGALRM error");
	pr_mask("starting main:");
	if(setjmp(jmpbuf)){
		pr_mask("ending main:");
		exit(0);
	}
	canjump=1;
	for( ; ;)
		pause();
}
