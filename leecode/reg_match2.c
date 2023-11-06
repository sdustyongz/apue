#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isMatch(char *s ,char * p){
    int m = strlen(s);
    int n = strlen(p);

    int f[m+1][n+1];
    memset(f,0,sizeof(f));
      
   
    f[0][0] = 1;
    int i ,j;
    for(j = 1;j <= n; j++){
        if(s[0] == p[j-1] || p[j-1] == '.'){
            f[0][j-1] =1;
            if(j < n && p[j] == '*'){
                j++;
            }else if(j < n && p[j] != '*'){
                break;
            }
        }else if(s[0] != p[j-1]){
            if(j < n && p[j] == '*'){
                    j++;
            }else{
                break;
            }
            
        }
    }

    // for(j = 1 ;j <= n ;j++){
    //     if(p[j-1] == s[0]||p[j-1] == '.'){
    //         f[0][j-1] = 1;
    //         break;
    //     }else if(p[j-1] == '*' || (j < n && p[j] == '*')){
    //         continue;
    //     }else if(j < n && p[j]!='*'){
    //         break;
    //     }
    // }
    for(i = 1;i <= m; i++){
        for(j = 1; j<= n;j++){
            if(s[i-1] == p[j-1] || p[j-1] == '.'){
                f[i][j] = f[i-1][j-1];
            }else if(p[j-1] == '*'){
               if(i>=2 && (p[j-2] == s[i-1] || p[j-2] =='.') && (s[i-1] == s[i-2] || p[j-2] == '.') ){
                f[i][j] = f[i-1][j-1] | f[i-1][j]|f[i][j-2];
               }else {
                f[i][j] = f[i][j-2] | f[i][j-1];
               } 
            }else {
                f[i][j] = 0;
            }
        }
    }
    return f[m][n];
}

int main(int argc,char *argv[]){
    //char * s ="bbcacbabbcbaaccabc";
    //char * p = "b*a*a*.c*bb*b*.*.*";
    //char  *s = "bbca";
    //char *p = "b*a*a*.c*bb*b*.*";
    char s[100];
    char p[100];
    while(true){
    gets(s);
    gets(p);
    printf("s:  %s\n p:  %s\n",s,p);
    int a = isMatch(s,p);
    printf("%d\n",a);
    }
   return 0;
}