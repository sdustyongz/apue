#include <stdlib.h>
#include <fcntl.h>

int main(int ac,char *av[]){
	if(ac<2)
		printf("user age:commond file \n");
	int fd;
	if((fd=open(av[1],O_RDONLY))==-1)
		perror("can not open file");
	int newfd=0;
	dup2(fd,newfd);
	lseek(fd,100,SEEK_CUR);
	off_t fdPos=lseek(fd,0,SEEK_CUR);
	off_t newfdPos=lseek(newfd,0,SEEK_CUR);
	printf("fdpos is %ld\n",fdPos);
	printf("newpos is %ld\n",newfdPos);
	int nnfd=0;
	if((nnfd=open(av[1],O_RDONLY))==-1)
		perror("can not open file");
	
	off_t nnfdPos=lseek(nnfd,0,SEEK_CUR);
	printf("nnpos is %ld\n",nnfdPos);

}
