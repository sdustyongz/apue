#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define INPUTLEN 100

void inthandler(int s){
	printf("received a signal %d\n",s);
	sleep(2);
	printf("leaving inthandler\n");
}

void quithandler(int s){
	
	printf("received a signal %d\n",s);
	sleep(3);
	printf("leaving quithandler\n");
}

int main(int ac,char *av[]){
	char input[INPUTLEN];
	int nchars;

	signal(SIGINT,inthandler);
	signal(SIGQUIT,quithandler);
	do{
		printf("\n type a message\n");
		nchars=read(0,input,(INPUTLEN-1));
		if(nchars==-1)
			perror("read return an error");
		else{
			input[nchars]='\0';
			printf("you typed ,%s",input);
		}
	}while(strncmp(input,"quit",4)!=0);
}

