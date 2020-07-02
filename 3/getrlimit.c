#include <sys/resource.h>
#include <stdio.h>
int main(int ac,char* av[]){
	struct rlimit rlim;
	getrlimit(RLIMIT_NOFILE,&rlim);
	printf("file count is :%d",rlim.rlim_max);
}
