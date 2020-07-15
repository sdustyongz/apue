#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t ntid;

void printids(char *s){
	pid_t pid;
	pthread_t tid;
	pid=getpid();
	tid=pthread_self();
	printf("%s pid %d tid %lu (0x%lx)\n",s,pid,tid,tid);
	
}

void * thr_fn(void *arg){
	printids("new thread: ");
	return ((void*)0);
}
int main(void){
	int err;
	err=pthread_create(&ntid,NULL,thr_fn,NULL);
	if(err!=0)
		perror("cant not create thread");
	printids("main thread:");
	sleep(1);
	return 0;
}
