#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>

struct mymsg{
    long mttype;
    char msg[512];
};

int main(int argc, char *argv[]){
   key_t  kt ;
    int quid;
    if((quid = msgget(kt,IPC_CREAT|0666)) ==-1){
        printf("create queue error\n");
        exit(1);
    } 

    struct mymsg msg;
    pid_t pid;
    if((pid = fork()) < 0){
        printf("fork error\n");
        exit(1);
    }

    if(pid == 0){
       while(msgrcv(quid,&msg, 512, 1,0) >= 0){
        printf("msg receive:%s\n",msg.msg);
       } 
       exit(0);
    }

    msg.mttype = 1;
    char * mm = "i am test ,hhh";
    int i = 0;
    while((*mm != '\0')&& i < 512){
        msg.msg[i++] = *mm++;     
    } 
    msg.msg[i] = '\0';
    msgsnd(quid, &msg, 512, 0);
    
    waitpid(pid,NULL, 0);
    return 0;
}