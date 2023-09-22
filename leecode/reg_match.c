#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool isMatch(char * s, char * p){
    char * pl = p;
    char c,previous ;
    while((c = *pl) != '\0' && *s != '\0'){
        if(c == '.'){
            previous = '.';
            s++;
            pl++;
        }
        else if(c >= 'a' && c <= 'z'){
            if(c == *s){
                s++;
                pl++;
                previous = c;
                continue;
            }else if(*(pl+1) != '\0' && *(pl+1) == '*'  ){
                if(*(pl+2) != '\0')
                    pl+=2;
                else {
                    pl +=2;
                    s++;
                    break;
                }
            }else{
                return false;
            }
        }else if(c == '*'){
           while(*s != '\0' && (*s == previous || previous == '.')) {
            previous = *s;
            s++;
           }
           if(*s == '\0' && *(pl+1) == '\0')return true;
           pl++;
           if(*pl == *s || *pl == '.'){
            *s++;
            *pl++;
           }
           else {
             s--;
           }

        }else {
            return false;
        }
    }
    if(*s == '\0' && *pl == '\0')return true;
    if(*s == '\0'){
        while(*pl != '\0'){
            if(*(pl+1) != '*' || *(pl+1) == '\0')
                return false;
            pl+=2;  
        }
        return true;
    }
    return false;
}

int main(int ac,char *argv[]){
    bool s = isMatch("bbbba",".*a*a");
    printf("%d\n",s);
}