#include <stdio.h>
#include <termios.h>
#include <fcntl.h>


void set_noecho_mode(){
	struct termios ttystate;

	tcgetattr(0,&ttystate);
	ttystate.c_lflag&=~ICANON;
	ttystate.c_lflag&=~ECHO;
	ttystate.c_cc[VMIN]=1;
	tcsetattr(0,TCSANOW,&ttystate);
}

void set_nodelay_mode(){
	int termflags;
	termflags=fcntl(0,F_GETFL);
	termflags|=O_NDELAY;
	fcntl(0,F_SETFL,termflags);
}


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

