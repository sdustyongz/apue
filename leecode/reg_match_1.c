#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int match_one_charact(char s ,char p){
    if(s == p) return 1;
    if(p == '.') return 1;
    if(p == '*') return 1;
    return 0;
}

bool isMatch(char * s, char * p){
    int m = strlen(s);
    int n = strlen(p);
    int checks[m][n];
    memset(checks,0,sizeof(checks));
    int i,j;
    for(i = 0;i < m;i++){
        for(j = 0;j <= i&&j<n ; j++){
            if(j == 0){
                if(i == 0 &&  match_one_charact(s[0],p[0])){
                    checks[0][0] = 1;
                    continue;
                }else  if(i == 0 && !match_one_charact(s[0],p[0])){
                    return false;
                }
                if(checks[i-1][0]){
                    if(p[0] == '*')
                        checks[i][0] = 1;
                    else checks[i][0] = 0; 
                }else{
                    checks[i][0] = 0;
                }
                continue;
            }


            if(checks[i-1][j-1] == 1){
                if(match_one_charact(s[i],p[j])){
                    checks[i][j] = 1;
                }else if(p[j-1] == '*'){
                    checks[i][j] = 1;
               }
            }else if(checks[i][j] != 1 &&checks[i-1][j] == 1){
                if(p[j] == '*')
                    checks[i][j] =1;
            }
        }
    }
    return checks[m-1][n-1] == 1;
}
int main(int arg, char *argv[]){
    char * s ="aab";
    char * p ="c*a*b";
    bool b = isMatch(s,p);
    printf("%d\n",b);
}

