#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define  MAXLINE 1024

int main(int argc, char *argv[]){
    char * ip_str = "192.145.211.11";
    struct in_addr ia;
    if(inet_pton(AF_INET,ip_str,&ia) == 1){
        printf("%d\n",ia.s_addr);
    }
    char ip[MAXLINE];
    char * ret_ip = inet_ntop(AF_INET,&ia, ip,MAXLINE);
    if(ret_ip != NULL){
        printf("ret ip is %s   , ip is %s\n",ret_ip,ip);
    }
}
