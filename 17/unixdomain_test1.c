#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <pthread.h>

#define NQ 3
#define MAXMSZ 512
#define KEY 0x123

struct threadinfo{
    int qid;
    int fd;
};

struct mymesg{
    long mtype;
    char mtext[MAXMSZ];
};

void * helper(void * arg){
    int  n;
    struct mymesg m;

    struct threadinfo *tip = (struct threadinfo *) arg;
    for(;;){
        memset(&m,0,sizeof(m));
        if((n = msgrcv(tip->qid, &m, MAXMSZ, 0, MSG_NOERROR)) < 0){
            printf("msgrcv error\n");
            perror("msgrcv error");
        }
        if(write(tip->fd,m.mtext,n) <0 ){
            perror("write error");
        }
    }
}

int main(int argc, char *argv[]){
    int i, n, err;
    int fd[2];
    int qid[NQ];
    struct threadinfo ti[NQ];
    struct pollfd pfd[NQ];
    ptrehad_t tid[NQ];
    char buf[MAXMSZ];

    for(i = 0; i < NQ; i++){
        if((qid[i] = msgget((KEY+i),IPC_CREAT|0666)) < 0){
            printf("msgget error \n");
            exit(1);
        }
        printf("queue ID %d  is %d\n",i,qid[i]);

        if(socketpair(AF_UNIX, SOCK_DGRAM, 0 ,fd) < 0){
            printf("socketpair error\n");
            exit(1);
        }
        ti[i].fd = fd[0];
        ti[i].qid = qid[i];

        pfd[i].fd = fd[1];
        pfd[i].events = POLLIN;

        if((err = pthread_create(&tid[i], NULL, helper, (void *)ti[i])) !=0){
            printf("pthread create error\n");
            exit(1);
        }

        for(;;){
            if(poll(pfd, NQ, -1) < 0){
                printf("poll error \n");
                exit(1);
            }
            for(i = 0; i < NQ; i++){
                if(pfd[i].revents & POLLIN){
                    if((n = read(pfd[i].fd, buf, sizeof(buf))) < 0){
                        printf("read error\n");
                    }
                    buf[n] = 0;
                    printf("queue id %d,message %s\n",qid[i], buf);
                }
            }
        }
    }
}


