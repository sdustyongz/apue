#include<stdio.h>
#include <stdlib.h>
#include<ncurses.h>
#include <signal.h>
#include <sys/time.h>
#include "settimer.c"
#include "termset.c"

#define COL_P 10 
#define ROW_P 10 
#define WALL_COL_MARGIN (COLS/3)
#define WALL_ROW_MARGIN (LINES/4) 

#define  RACKET_HIGH 5

#define KEYCODE_U 0x41
#define KEYCODE_D 0x42

struct ball{
	char symbol;
	int x_pos;
	int y_pos;
	int x_dir,y_dir,
	x_ttm,y_ttm,
	x_ttg,y_ttg;
};

struct ball bal;
void initwall(){
	initscr();
	move(COL_P,ROW_P);
	standout();
	for(int i=COL_P;i<COLS-WALL_COL_MARGIN;i++){
		move(ROW_P,i);
		addstr(" ");
	}
	for(int i=ROW_P;i<LINES-WALL_ROW_MARGIN;i++){
		move(i,COL_P);
		addstr(" ");
	}
	
	for(int i=COL_P;i<COLS-WALL_COL_MARGIN;i++){
		move(LINES-WALL_ROW_MARGIN,i);
		addstr(" ");
	}
	
	standend();
	refresh();
		
}

void  ball_move(int s){
	struct ball * ball=&bal;
	move(ball->y_pos,ball->x_pos);
	addch(' ');
	if(--ball->x_ttg==0){
		ball->x_ttg=ball->x_ttm;
		if(ball->x_pos<=COL_P+1||ball->x_pos>=(COLS-WALL_COL_MARGIN-1))
			ball->x_dir*=-1;
		bal.x_pos+=bal.x_dir;
	}
	if(--ball->y_ttg==0){
		ball->y_ttg=ball->y_ttm;
		if(ball->y_pos<=ROW_P+1||ball->y_pos>=(LINES-WALL_ROW_MARGIN-1))
			ball->y_dir*=-1;
		bal.y_pos+=bal.y_dir;
	}
	move(ball->y_pos,ball->x_pos);
	addch(ball->symbol);
	move(COLS,LINES);
	refresh();
}

struct racket{
	int row,col;
	int height;
};
struct racket rk;
void draw_racket(){
    standout();
	rk.row=COLS-WALL_COL_MARGIN+1;
	rk.col=ROW_P+1;
	rk.height=RACKET_HIGH;
	for(int i=0;i<RACKET_HIGH;i++){
		move(ROW_P+1+i,COLS-WALL_COL_MARGIN+1);
		addstr(" ");
	}

	standend();
	refresh();
}

void move_racket(){
	char c;
	while(read(0,&c,1)>0){
		switch(c){
			case KEYCODE_U:
					
				break;
			case KEYCODE_D:
				break;
			case 'q':
			    exit(0);
		  default:
		  ;
		
		}
	}
}


int main(int ac,char*av[]){
	bal.symbol='o';
	bal.x_pos=COL_P+2;
	bal.y_pos=ROW_P+2;
	bal.x_dir=1;
	bal.y_dir=1;
	bal.x_ttg=2;
	bal.y_ttg=3;
	bal.x_ttm=2;
	bal.y_ttm=3;
	initwall();
	draw_racket();
	int g=getchar();	
	signal(SIGALRM,ball_move);
	set_ticker(1000/20);
	int ch=getchar();
	endwin();
}

