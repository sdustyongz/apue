#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <ncurses.h>
#include<sys/time.h>
#include <termios.h>

#define MSG "O" 
#define INTERVEL_MIS 50

static int row=0;
static int col=0;
static int move_intervel=100;
static int direct=1;



void init_screen(){
	initscr();
	clear();
}

void move_msg(){
		
	move(row,col);
	addstr("    ");
	col+=direct;
	move(row,col);
	addstr(MSG);
	refresh();
	if(direct==-1&&col<=0)
		direct=1;
	else if(direct==1&&col>=COLS)
		direct=-1;
}

void speed(){
	move_intervel+=INTERVEL_MIS;
}

int set_delay(){
	 struct itimerval new_time; 
	 long sec=move_intervel/1000;
	 long millison=(move_intervel%1000)*1000L;

	new_time.it_interval.tv_sec=sec;
	new_time.it_interval.tv_usec=millison;
	
	new_time.it_value.tv_sec=sec;
	new_time.it_value.tv_usec=millison;
	return setitimer(ITIMER_REAL,&new_time,NULL);
}

void redirect(){
	direct=-direct;
}

void no_echo_mode(){
	struct termios t;
	tcgetattr(0,&t);
	t.c_lflag|=~ICANON;
	t.c_lflag|=~ECHO;
	t.c_cc[VMIN]=1;
	tcsetattr(0,TCSANOW,&t);
}
int main(int ac,char *av[]){
	init_screen();
	no_echo_mode();
	signal(SIGALRM,move_msg);
    set_delay();	
	getch();
	endwin();
}
