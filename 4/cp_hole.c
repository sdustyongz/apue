#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024

int write_buf(char * buf,int length,int hole){
   int i = 0;
   for(;i<length;i++ ){
    if(hole && *(buf+i) != '\0')
        break;
    if(!hole && *(buf+i) == '\0')
        break;
   }
   return i;
}

int cp(int sc_fd,int target_fd){
    char buf[SIZE];
    int n=0;
    int c_cnt;
    int i=0;
    while((n = read(sc_fd,buf,SIZE)) > 0){
        i=0;
       for(;i < n;){
          
         if(buf[i] == '\0'){
            c_cnt =  write_buf(buf+i,n-i,1);
            if(lseek(target_fd,c_cnt,SEEK_CUR) < 0){
                perror("ddd");
                return;
            }
         }
         else{
            c_cnt = write_buf(buf+i,n-i,0);
            write(target_fd,buf+i,c_cnt);
         } 
         i+=c_cnt;
       }
    }
}


int main(int ac,char*av[]){
   if(ac < 3){
        printf("usage error \n");
        return 1;
   }
   int scfd = open(av[1],O_RDWR);
   int targertfd = open(av[2],O_CREAT|O_RDWR);
   if(targertfd <0 ){
        perror("ss:");
        return 2;
   }
   cp(scfd,targertfd);
   return 0;
}
