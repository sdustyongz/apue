#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAXLEN 1024


static void  err_doit(int errnoflag,int error,const char * fmt,va_list ap){
	char buf[MAXLEN];
	vsnprintf(buf,MAXLEN-1,fmt,ap);
	if(errnoflag)
		snprintf(buf+strlen(buf),MAXLEN-strlen(buf)-1," :%s",strerror(error));
	strcat(buf,"\n");
	fflush(stdout);
	fputs(buf,stderr);
	fflush(NULL);
}

void err_ret(const char *fmt,...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);
}

void err_exit(int err,const char * fmt,...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,err,fmt,ap);
	va_end(ap);
	exit(1);
}
void err_dump(const char * fmt,...){
	va_list ap;
	va_start(ap,fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);
	abort();
	exit(1);
}




