#include <stdio.h>
#include <stdlib.h>

#define MAX_INT ((unsigned)-1 >> 1)
#define MIN_INT (~MAX_INT)


int reverse(int x){
    if(x == 0) return 0;
    int max_int_divide10 = MAX_INT/10; 
    int sign = 1;
    if(x < 0) {
       sign = -1; 
    }
    int n = 0;
    int y = 0;
    while(x != 0){
        n = n*10+(x%10);
        y = x/10; 
        if(n > max_int_divide10 && y > 0) return 0;
        if(y == 0 ){
            if(sign == 1){
                if(x > 7) return 0;
            }else if(x < -8) {
                return 0;
            }
        }
        x = y;
    }
    return n;

}

int main(int argc, char *argv[]){
    int n = reverse(-123);
    printf("%d\n",n);
    printf("%d\n",MAX_INT);
}