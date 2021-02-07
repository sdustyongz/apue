#include <stdio.h>
#include <unistd.h>

void print_process(char * s){
	printf("%s info is  pid:%d,ppid:%d,pgid:%d,sid:%d,pgrpid:%d\n",s,getpid(),getppid(),getpgrp(),getsid(0),tcgetpgrp(STDIN_FILENO));
}


