#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * circle(char * str, int length){

    int data[length][length];
    int step = 2;
    int i ,j ;
    memset(data,0,sizeof(data));
    for(i = 0 ;i < length; i++){
        data[i][i] = 1;
        if((i < length -1)&&(str[i] == str[i+1])){
            data[i][i+1] = 2;
        }
    }
    while(step < length){
        i = 0;
        j = step;
       while(j < length){
        if(str[i] == str[j])
            data[i][j] = data[i+1][j-1] + 2; 
        else  data[i][j] = 0;
        i++;
        j = i + step;
       } 
       step++;
    }
    int start = 0,end = 0;
    int max = 0;
    for (i = 0 ;i < length; i++){
        for(j = 0; j < length; j++)
            if(data[i][j] > max ){
                max = data[i][j];
                start = i ;
                end = j;
            }
    }
    printf("max %d , start %d, end %d\n",max,start,end);
        char * s = malloc(end -start+2);
        i = 0;
        for(;start <= end;start++)
            *(s+ (i++)) = str[start]; 
        s[i]='\0';
        return s;
}

int main(int argc, char * argv[]){
    char * s = circle("ccc",3);
    printf("%s\n",s);
}