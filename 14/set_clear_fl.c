#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void set_fl(int fd,int flags){

	int val;
	if((val=fcntl(fd,F_GETFL,0))<0)
		perror("fcntl FGETFL failure");
	val|=flags;
	if(fcntl(fd,F_SETFL,val)<0)
		perror("fcntl SETFL error");
}
void clr_fl(int fd,int flags){
	
	int val;
	if((val=fcntl(fd,F_GETFL,0))<0)
		perror("fcntl FGETFL failure");
	val&=!flags;
	if(fcntl(fd,F_SETFL,val)<0)
		perror("fcntl SETFL error");
}
