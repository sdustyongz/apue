#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include "daemonize.h"

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
}