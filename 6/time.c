#include  <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(int ac , char * av[]){
    time_t t;
    time_t tt = time(&t);
    printf("t:%ld       tt:%ld\n",t,tt);

    struct timespec ts;

    if(clock_gettime(CLOCK_REALTIME ,&ts) != -1){
         printf("second:%ld       nsec:%ld\n",ts.tv_sec,ts.tv_nsec);
    }

    struct tm * ltm =localtime(&t);
    char buf[20];
    strftime(buf,20,"%F",ltm);
    printf("%s\n",buf);
    
}