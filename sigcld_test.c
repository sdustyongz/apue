#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void sig_cld(int code){
	pid_t pid;
	int status;
	printf("SIGCLD received\n");
	if(signal(SIGCLD,sig_cld)==SIG_ERR)
		perror("signal error");
	if((pid=wait(&status))<0)
		perror("wait error");
}

int main(int ac,char * av[]){
	pid_t pid;
	if(signal(SIGCLD,sig_cld)==SIG_ERR)
		perror("signal error");
	if((pid=fork())<0)
		perror("fork error");
	else if(pid==0){
		sleep(2);
		exit(2);
	}

	pause();
	exit(0);

}
