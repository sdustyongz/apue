#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

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


    sethostent(0);
    struct hostent * hte;
    char * aliase;
    char ** aliases ;
    while((hte = gethostent()) != NULL){
        printf("hname is %s , type is %d\n",hte->h_name,hte->h_addrtype);
        printf("-------------------------------\n");
        printf("hAliases:\n");
        aliases = hte->h_aliases;
        while((aliase = *aliases++) != NULL){
            printf("           %s\n",aliase);
        }
        printf("-------------------------------\n");
        aliases = hte->h_addr_list;
        printf("addr_list :\n");
        while((aliase = *aliases++) != NULL){
            printf("           %s\n",aliase);
        }
    }
    endhostent();

    setnetent(0);
    struct netent * ne;

    while((ne = getnetent()) != NULL){
        printf("netent namte:%s\n, addrtype:%d, ip is %s\n",ne->n_name,ne->n_addrtype,inet_ntop(AF_INET,&ne->n_net,NULL,0));
        aliases = ne->n_aliases;
        printf("aliases :\n");
        while((aliase = *aliases++) != NULL){
            printf("           %s\n",aliase);
        }

    }
    endnetent();
}
