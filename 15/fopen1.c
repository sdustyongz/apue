#include <stdio.h>
#include <stdlib.h>

#define PAGER "${PAGER:-more}"
#define MAXLINE 2048

int main(int argc, char *argv[]){
  char line[MAXLINE];
  FILE *fpin, *fpout;

  if(argc != 2){
    printf("usage : a.out <infilepath>\n");
    exit(1);
  }

  if((fpin = fopen(argv[1],"r")) == NULL){
   printf("can't open %s\n", argv[1]);
   exit(1); 
  }

  if((fpout = popen(PAGER,"w")) == NULL){
   printf("can't popen %s\n", PAGER);
   exit(1); 
  }

  while(fgets(line,MAXLINE,fpin) != NULL){
    if(fputs(line,fpout) == EOF){
        printf("puts error\n");
        exit(1);
    }
  }
  if (ferror(fpin)){
    printf("gets error\n");
    exit(1);
  }
  if(pclose(fpout) == -1){
    printf("pclose error \n");
  }
  exit(0);
}