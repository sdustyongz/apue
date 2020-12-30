#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <fcntl.h>

#define LINE_SIZE 24



int linecount=0;

void tty_mode(int how){
	static struct termios original_mode;
	static int original_flags;
	static int stored=0;
	if(how==0){
		tcgetattr(0,&original_mode);
		original_flags=fcntl(0,F_GETFL);
		stored=1;
	}else if(stored){

		tcsetattr(0,TCSANOW,&original_mode);
		fcntl(0,F_SETFL,original_flags);
	}
}

int ask_more(){
	int ch;
	while((ch=getchar())){
		
		switch (ch){
			case ' ':
				return 1;
		case 'q':
			return 0;
		}
	}
}

void read_page(FILE * FILE){
	char line[200];
	while(fgets(line,200,FILE)!=NULL){
		puts(line);
		if(++linecount==LINE_SIZE){
			int more=ask_more();
			if(more==0)
				return;
			else if(more==1){
				linecount=0;
				continue;
			}
		}
	}
}

void set_cr_noecho_mode(){
	struct termios ttymode;
	tcgetattr(0,&ttymode);
	ttymode.c_lflag&=~ICANON;
	ttymode.c_lflag&=~ECHO;
	ttymode.c_cc[VMIN]=1;
	tcsetattr(0,TCSANOW,&ttymode);
}

int main(int ac,char *av[]){
	if(ac<2){
		printf("parameter is wrong \n");
		return -1;
	}

	FILE * fp;
	fp=fopen(av[1],"r");
	tty_mode(0);
	set_cr_noecho_mode();
	read_page(fp);
	tty_mode(1);
	fclose(fp);
	return 0;
}
