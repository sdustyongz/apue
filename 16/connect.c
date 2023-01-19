#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "connect.h"

#include <netinet/in.h>

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol, struct sockaddr *addr, socklen_t alen){
    int numsec, fd;
    for(numsec = 1; numsec <= MAXSLEEP; numsec <<=1){
        if((fd = socket(domain, type, protocol)) < 0)
            return -1;
    
        if(connect(fd, addr, alen) == 0)
            return fd;
        close(fd);

        if(numsec <= MAXSLEEP/2)
            sleep(numsec);
    }

    return -1;

}

void print_uptime(int sockfd){
    int n;
    char buf[BUFSIZ];
    while((n = recv(sockfd,buf,BUFSIZ, 0)) > 0){
        write(STDOUT_FILENO, buf, n);
    }
}

int main(int ac, char *argv[]){
    if(ac < 3){
        printf("useage a.out servicehost port");
        exit(1);
    }
    char * serverhost = argv[1];
    int port = atoi(argv[2]);

    struct in_addr in;
    if(inet_pton(AF_INET,serverhost, &in) != 1){
        printf("host %s error\n",serverhost);
        exit(1);
    
    }

    struct sockaddr_in si;
    si.sin_family = AF_INET;
    si.sin_addr = in;
    si.sin_port = htons(port);

    int sockfd ;
    printf("connect for %s:%d",serverhost,port);

    if((sockfd = connect_retry(AF_INET, SOCK_STREAM, 0, &si, sizeof(si))) < 0){
        printf("connect failure \n");
        exit(1);
    }
    print_uptime(sockfd);

}