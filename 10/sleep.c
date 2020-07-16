#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_sleep(int signo){
	
}

int sleep1(int second){
	struct sigaction new_action,old_action;
	sigset_t new_mask,old_mask,sus_mask;
	sigemptyset(&new_mask);
	sigaddset(&new_mask,SIGALRM);
	sigprocmask(SIG_BLOCK,&new_mask,&old_mask);
	new_action.sa_handler=alarm_sleep;
	new_action.sa_flags=0;
	new_action.sa_mask=old_mask;
	
	sigaction(SIGALRM,&new_action,&old_action);
	sus_mask=old_mask;
	sigdelset(&sus_mask,SIGALRM);
	alarm(second);
	sigsuspend(&sus_mask);
	
	int unslept=alarm(0);
	sigaction(SIGALRM,&old_action,NULL);
	sigprocmask(SIG_SETMASK,&old_mask,NULL);
	return unslept;

}
int main(){
	printf("left is %d\n",sleep1(100));
}
