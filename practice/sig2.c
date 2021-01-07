#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define INPUTLEN 100


void inthandler(int s){
	printf("receive a signal %d\n",s);
	sleep(3);
	printf("done handling signal %d\n",s);
}

int main(int ac,char *av[]){
	struct sigaction newhandler;
	newhandler.sa_handler=inthandler;
//	newhandler.sa_flags=SA_RESTART;
	sigset_t blocked;

	sigemptyset(&blocked);
	sigaddset(&blocked,SIGQUIT);
	newhandler.sa_mask=blocked;

	char x[INPUTLEN];

	
	if(sigaction(SIGINT,&newhandler,NULL)==-1)
		perror("sigaction");
	else
		while(1){
			if(read(0,x,INPUTLEN)==-1){
				perror("read happen error");
			}else{
					printf("input: %s",x);
			}
		}


}
