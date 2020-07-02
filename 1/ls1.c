#include <stdio.h>
#include <dirent.h>

int main(int ac,char *av[]){
	DIR * dp;
	struct dirent *dirp;
	if(ac<2)
		perror("useage :  is Directory name");
	if((dp=opendir(av[1]))==NULL){
		perror("dir can not open");	
	}
	while((dirp=readdir(dp))!=NULL){
		printf("%s\n",dirp->d_name);
	}
}
