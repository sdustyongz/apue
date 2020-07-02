#include <stdlib.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/errno.h>


int dup2(int oldfd,int newfd){
	int ret;
	int count=0;
	struct rlimit  rlim;
	getrlimit(RLIMIT_NOFILE,&rlim);
	
	int stack[rlim.rlim_cur];
	if(newfd<0||newfd>rlim.rlim_cur-1){
		errno=EBADF;
		return -1;
	}
	while(1){

		ret=dup(oldfd);
		if(ret==-1&&errno!=EMFILE){
			break;
		}else if(ret==-1&&errno==EMFILE){
			if(newfd==oldfd)
				return newfd;
			printf("close newfd\n");
			close(newfd);
		}else{

			if(oldfd==newfd){
				close(ret);
				return newfd;
			}
			if(ret==newfd)
				break;
			else if(ret<newfd)
				stack[count++]=ret;
			else{
				close(ret);
				printf("close new fd \n");
				close(newfd);
			}
		}
	}
	while(count){
		close(stack[--count]);
	}

	return ret;
	
}

int main(){
	int fd=dup2(0,10000);
	printf("fd%d\n",fd);
	
}
