#include <signal.h>
#include <unistd.h>
#include <stdio.h>
void sig_alarm(int sino){
	printf("caugt a alarm\n");	

}
int sleep1(int second){
	if(signal(SIGALRM,sig_alarm)==SIG_ERR)	
		return second;
	alarm(second);
	pause();
	return alarm(0);
}

int main(int ac,char *av[]){
	alarm(5);
	int unslep=sleep1(1);
	printf("sleep over,left second is %d\n",unslep);
}
