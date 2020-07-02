#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int creathole(char * path,int len){
	int fd;
	if((fd=open(path,O_RDWR|O_CREAT,S_IRWXU|S_IRWXG))==-1)
		perror("can not open file");
	lseek(fd,len,SEEK_SET);
	write(fd,"name",4);
	lseek(fd,0,SEEK_SET);
	return fd;

}

int main(int ac,char * av[]){
	int fd=creathole(av[1],atoi(av[2]));
	char buf[1024];
	int len=0;
	while((len=read(fd,buf,1024))>0)
		write(STDOUT_FILENO,buf,len);
}
