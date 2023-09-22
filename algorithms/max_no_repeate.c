#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cal(char * str, int i ,int j){
    int index = i;
    char c = str[j];
    while(index < j){
        if(str[index] == c)
            return 0;
        index++;
    }
    return 1;
}

char *lengthOfLongestSubstring(char * str){
    int length = strlen(str);
    int d[length][length];
    memset(d,0,sizeof(d));
    int i ,j,max_start = 0;
    int step = 1;
    int max = 1;
    int val;
    for(i = 0;i < length; i++) 
        d[i][i] = 1;
    while(step < length){
       i = 0;
        for(j = i+step;j < length;){
                val = cal(str,i,j);
                if(val == 0){
                    d[i][j] = 0;
                }else{
                    d[i][j] = d[i][j-1]+1;
                }

                if(max < d[i][j]){
                    max = d[i][j];
                    max_start = i;
                }
            i ++;
            j=i+step;    
        }
        step++;
    }

    char * ret = malloc(max+1);
    for(i = 0;i < max;i++){
        ret[i] = str[max_start+i];
    }
    ret[max] = '\0';
    return ret;
}

int main(int argc, char *argv[]){
    char *str = "dvdf";
    char * s = lengthOfLongestSubstring(str);
    printf("%s\n",s);
    return 0;
}