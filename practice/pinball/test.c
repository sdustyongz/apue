#include <stdio.h>

struct ball{
int x;
		};

int main(){
	struct ball ball;
	ball.x=10;
	while(--ball.x>0)
		printf("aa\n");
}
