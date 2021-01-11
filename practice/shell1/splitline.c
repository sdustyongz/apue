#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define is_delim(x) ((x)==''||(x)=='\t')

extern int execute(char ** argv);

void fatal(char * s1,char *s2,int n){
	fprintf(stderr,"error:%s,%s\n",s1,s2);
	exit(n);
}
void * emalloc(size_t n){
	void * rv;
	if((rv=malloc(n))==NULL)
		fatal("out of memory","",1);
	return rv;
}

void * eremalloc(void *p,size_t n){
	void * rv;
	if((rv=realloc(p,n))==NULL)
		fatal("realloc() failed","",1);
	return rv;
}



char * next_cmd(){
	int cmd_len=0;
	int size=0;
	int ch;
	char * cmd;
	while((ch=getchar())!='\n'){
		if(cmd_len+1>=size){
			if(size==0)
				cmd=emalloc(BUFSIZ);
			else
				cmd=eremalloc(cmd,BUFSIZ+cmd_len);
			size+=BUFSIZ;
		}
		if(cmd_len<size){
			*(cmd+cmd_len++)=ch;	
		}
	}
	*(cmd+cmd_len)='\0';
	return cmd;

}

char * new_str(char * str,int len){
	char * rs=emalloc(len+1);
	
	for(int i=0;i<len;i++)
		*(rs+i)=*str++;
	*(rs+len)='\0';
	return rs;
}

char ** split_command(char * cmd){
	char * start=cmd;
	int token_len=0;
	int slot=20;
	char ** args=emalloc(slot*sizeof(char *));
	int arg_count=0;
	while(*cmd!='\0'){
		if((*cmd==' '||*cmd=='\t')){
			if(token_len==0)
				{   cmd++;
					continue;
				}
			if(arg_count+1>slot){
				slot+=10;
				args=emalloc(slot*sizeof(char *));
			}
			char * dd=new_str(start,token_len);
			args[arg_count++]=dd;
			token_len=0;
		}else{
			if(token_len==0)
				start=cmd;
			token_len++;
		}
		cmd++;
	}
	if(token_len>0)
		args[arg_count++]=new_str(start,token_len);
	args[arg_count]=NULL;
	return args;
}

void  freelist(char ** args){
	char ** cp=args;	
	while(*cp)
		free(*cp++);
	free(args);
}

int main(int ac,char **av){	
	char * cmd;
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	while((cmd=next_cmd())!=NULL){
		char ** args=split_command(cmd);	
		if(args!=NULL){
			execute(args);		
			freelist(args);
		}
		free(cmd);
	}
}
