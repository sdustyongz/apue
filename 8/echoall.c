#include <stdio.h>

int main(int ac,char *av[]){
	int i;
	char ** ptr;
	extern char ** environ;

	for(i=0;i<ac;i++)
		printf("argv[%d]:%s\n",i,av[i]);
	for(ptr=environ;*ptr!=0;ptr++)
		printf("%s\n",*ptr);
	return 0;
}
