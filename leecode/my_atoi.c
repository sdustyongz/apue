#include <stdio.h>
#include <stdlib.h>

#define MAX_INT ((unsigned)-1 >> 1)
#define NEG_MIN_INT  (1 + MAX_INT)

int myAtoi(char * s){
    int ret = 0;
    char c;
    short sign = 1;
    int n = 0; 
    int max_threshold = MAX_INT / 10;
    
    while((c = *s++) != '\0' && c == ' ');
    if(c == '-') sign = -1;
    if(c >= '0' && c <= '9') n = c - '0';
    else return n;
    while((c = *s++) != '\0' && c >= '0' && c<='9' ){
        if(n < max_threshold){
            n = n*10 + (c - '0');
        }else if(n == max_threshold){
            if(sign == 1){
                if(c - '0' > 7) return MAX_INT;
                else return n*10 + (c - '0');
            }else{
                if(c > '8') return NEG_MIN_INT;
                else return (-1)*n*10-(c - '0');
            }
        }else{
            if(sign == 1){
                return MAX_INT;
            }else {
                return NEG_MIN_INT; 
            }
        }
        
    }
    return sign*n;
}

int main(int argc,char *argv[]){
    int n = myAtoi("42");
    printf("%d\n",n);
}