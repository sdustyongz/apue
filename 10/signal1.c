#include <stdio.h>
#include <signal.h>
#include <unistd.h>

typedef void Sigfunc(int);

Sigfunc * signal1(int signo,Sigfunc * fun){	
	struct sigaction act,oact;
	printf("invoke signal\n");
	act.sa_handler=fun;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	if(signo==SIGALRM){
		#ifdef SA_INTERRUPT
			act.sa_flags|=SA_INTERRUPT;
		#endif
	}else{
		act.sa_flags|=SA_RESTART;
	}
	if(sigaction(signo,&act,&oact)<0)
		return SIG_ERR;
	return oact.sa_handler;
}

void sig_quilt(int signo){
	printf("receive quilt \n");
	sleep(5);
}
void sig_alarm(int signo){
	printf("hello ,i am receive a alarm!!!\n");
}
int main(int ac,char * av[]){
	signal1(SIGQUIT,sig_quilt);
	for(;;)
	  pause();
}
