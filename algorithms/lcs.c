#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getMaxLen(int * c[], int i, int j);

int lcs(char * str1 ,int len1, char * str2, int len2){
    int c[len1][len2];
    int i,j;
    for(i = 0 ; i < len1; i++){
        for(j = 0; j < len2; j++){
           if(str1[i] == str2[j]){
                if(i == 0 || j == 0)
                    c[i][j] = 1;
                else c[i][j] = c[i-1][j-1]+1;
           }else{
            // c[i][j] = getMaxLen(c,i,j);
                if(i <= 0 || j <= 0)
                    c[i][j] = 0;
                else if(c[i-1][j] > c[i][j-1]){
                    c[i][j] = c[i-1][j];
                } else{
                    c[i][j] = c[i][j-1];
                }
           } 
        
        }
    }
    for(i = 0; i < len1; i++){
        for(j = 0; j < len2; j++){
            printf("%d  ",c[i][j]);
        }
        printf("\n");
    }

    
}

int getMaxLen(int **c, int i, int j){
    if(i <= 0 || j <= 0){
        return 0;
    }
    if(c[i-1][j] > c[i][j-1])
        return c[i-1][j];
    return c[i][j-1];
}

int main(int argc, char * argv[]){
    lcs("abcd",4,"abc",3);
}