#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int count=0;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
void * addTenThousand(){
	int i=0;
	for(;i<10000;i++){
		pthread_mutex_lock(&mtx);
		count++;
		pthread_mutex_unlock(&mtx);
	}
}

int main(){
	int thread_count=10;
	pthread_t tid[thread_count];
	for(int i=0;i<thread_count;i++){
		pthread_create(&tid[i],NULL,addTenThousand,NULL);
	}
	for(int i=0;i<thread_count;i++){
		void * ret;
		pthread_join(tid[i],&ret);
	}

	printf("count is %d\n",count);
}
