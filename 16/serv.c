#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include "daemonize.h"
#include <syslog.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>

#define BUFLEN 128 
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256 
#endif

int initserver(int type,struct  sockaddr *addr, socklen_t alen, int qlen){
    int fd;
    int err = 0;

    if((fd = socket(addr->sa_family, type, 0)) < 0){
        printf("socket error\n");
        return -1;
    }

    if(bind(fd, addr, alen) < 0)
        goto errout;
    if(type == SOCK_STREAM || type == SOCK_SEQPACKET){
        if(listen(fd, qlen) < 0)
            goto errout;
    }
    return fd;
    errout:
        err = errno;
        close(fd);
        errno = err;
        return -1;
}

void serve(int sockfd){
    int clfd;
    FILE *fp;
    char buf[BUFLEN];

    for(;;){
        if((clfd = accept(sockfd,NULL,NULL)) < 0){
            syslog(LOG_ERR,"ruptimed:aactpt error %s",strerror(errno));
            exit(1);
        }

        if((fp = popen("/usr/bin/uptime","r")) == NULL){
            sprintf(buf, "error: %s\n", strerror(errno));
            send(clfd, buf, strlen(buf), 0);
        }else{
            while(fgets(buf,BUFLEN,fp) != NULL)
                send(clfd, buf, strlen(buf), 0);
            pclose(fp);
        }
        close(clfd);

    }

}

int main(int argc, char * argv[]){
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int sockfd, err, n;
    char *host;

    if(argc != 1){
        printf("usage: ruptimed\n");
        exit(1);
    }
    if((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
        n = HOST_NAME_MAX;
    if((host = malloc(n)) == NULL){
        printf("malloc error\n");
        exit(1);
    }
    if(gethostname(host,n) < 0){
        printf("gethostname error\n");
        exit(1);
    }
    printf("hostname is %s\n",host);
    daemonize("ruptimed");
    
    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if((err = getaddrinfo(host,"ruptime", &hint, &ailist)) != 0){
        //syslog(LOG_ERR, "ruptimed: getaddrinfo error ");
        struct sockaddr_in in ;
        in.sin_family = AF_INET;
        struct in_addr ina;
        ina.s_addr = htonl(INADDR_ANY);
        in.sin_addr = ina;
        in.sin_port = htons(9005);
                serve(sockfd);
                exit(0);
        }

        exit(1);
    }
    for(aip = ailist; aip != NULL; aip = aip->ai_next){
        if((sockfd = initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen, QLEN)) >=0 ){
            serve(sockfd);
            exit(0);
        }
    }
    return 0;
}