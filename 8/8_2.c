#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int f1(){
	pid_t pid;
	pid=vfork();
	return pid;
}

int f2(){
	return 100;
}
int main(){

	pid_t pp=f1();
	f2();

	printf("pid is %d,pp is %d\n",getpid(),pp);
}

