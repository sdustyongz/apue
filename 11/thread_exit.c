#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * th1(){
	printf("thread 1 running ,tid is %ld\n",pthread_self());
	return (void *)1;
	
}

void * th2(){
	printf("thread 2 running ,tid is %ld\n",pthread_self());
	pthread_exit((void *)2);
}

int main(){
	pthread_t td1;
	pthread_t td2;
	int err;
	err=pthread_create(&td1,NULL,th1,NULL);
	if(err!=0)
		perror("create thread1 fail");
	printf("in main thread1 id is %ld\n",td1);
	err=pthread_create(&td2,NULL,th2,NULL);
	if(err!=0)
		perror("create thread2 fail");
	void * ret;
	err=pthread_join(td1,&ret);
	if(err!=0)
		perror("join thread1 fail");
	printf("thread exit value is %ld\n",(long)ret);
	
	err=pthread_join(td2,&ret);
	if(err!=0)
		perror("join thread2 fail");
	printf("thread1 exit value is %ld\n",(long)ret);
	

}
