#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

#define oops(m,x) {perror(m);exit(x);}


void exedc(int todc[2] ,int fromdc[2]){
	close(todc[1]);
	close(fromdc[0]);
	
	if(dup2(todc[0],0)==-1)
			oops("",1);
	if(dup2(fromdc[1],1)==-1)
			oops("",1);
	int ch;
	execlp("dc","dc","-" ,NULL);
	oops("can not exec",1);
}

int main(int ac,char *av[]){
	int todc[2];
	int fromdc[2];
	if(pipe(todc)==-1||pipe(fromdc)==-1)
		oops("",1);
	int pid;
	if((pid=fork())==-1)
		oops("can not fork",1);
	if(pid==0){
		exedc(todc,fromdc);
	}else{
		close(todc[0]);
		close(fromdc[1]);
	//	if(dup2(fromdc[0],1)==-1)
	//		oops("",1);
		int num1,num2;
		char operation;
		if(scanf("%d%c%d",&num1,&operation,&num2)!=3){
			oops("input syntax error",1);
		}
		FILE * wr=fdopen(todc[1],"w");
		fprintf(wr,"%d\n%d\n%c\np\n",num1,num2,operation);
		fflush(wr);
		FILE * rr=fdopen(fromdc[0],"r");
		char ms[1024];
		if(fgets(ms,1024,rr)!=NULL)
			printf(" the result is:%s\n",ms);
	}
}
