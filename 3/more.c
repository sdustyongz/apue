#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int see_more(){
	printf("q:quit, :more\n");
	char c;
	while((c=getchar())!=EOF){
		if(c=='q'){
			return 0;
		}else if(c==' '){
			return 1;
		}else{
		}
	}
}
void do_more(int fd,int len){
	int count=0;
	char buf[BUFSIZ];
    int lineCount=0;
	while((count=read(fd,buf,BUFSIZ))>0){
		int i=0;
		for(i=0;i<count;i++){
			if(buf[i]=='\n')
				if(++lineCount==len)
					break;
		}
		if(i<count){
			off_t pos=0;
			if((pos=lseek(fd,i-count,SEEK_CUR))==-1)
				perror("lseek fail");
		}
		if(i>0)	
			write(2,buf,i);
		if(len==lineCount){
			lineCount=0;	
			int r=see_more();
			if(r==0){
				break;
			}
		}
		count=-1;
	}

}

int main(int ac,char*av[]){

	setbuf(stdin,NULL);
	int fd=open(av[1],O_RDWR);
	do_more(fd,4);
}
