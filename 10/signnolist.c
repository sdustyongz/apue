#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

const char * sig2str1(int signo){ 
	extern const char *const sys_siglist[];
	if(signo<=0||signo>_NSIG)
		return "";\
	return sys_siglist[signo];

}

int main(int ac,char*av[]){
	printf("%s\n",sig2str1(1));
	printf("%s\n",sig2str1(2));
	printf("%s\n",sig2str1(3));
	printf("%s\n",sig2str1(4));
	printf("%s\n",sig2str1(5));
	printf("%s\n",sig2str1(6));
	printf("%s\n",sig2str1(7));
}
