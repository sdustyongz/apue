#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *  lengthOfLongestSubstring(char * str){
    if(str == NULL || *str == '\0'){
        char * s = (char*)malloc(sizeof(char));
        s[0] = '\0';
        return s;
    } 
    char * left = str,*right =str+1;
    int max = 1;
    char * max_p  = str;
    uint64_t map[4];
    map[*str/64] |=  1 << (*str%64);
    
    while(*right != '\0'){
        if((map[*right/64] & (1L << (*right%64))) !=0 ){
            printf("%c,%c\n",*left,*right);
            if(right - left > max){
                max = right -left ;
                max_p = left;
            }
            while(*left  != *right){
                left++;
            }
            if(left < right)
                left++;
            memset(map,0,sizeof(map));
            for(int j = 0;j < right-left-1;j++){
                map[*(left+j)/64] |=  (1L << (*(left+j)%64));
            }
        }else{
            map[*right/64] |=  (1L << (*right%64));
            right++;
        }
    }
    if(right-left > max){
        max = right-left;
        max_p = left;
    }

    char * s = (char*)malloc((max+1)*sizeof(char));
    for(int i = 0;i < max;i++){
        s[i] = *max_p++;
    }
    s[max] = '\0';
    printf("max is %d\n",max);
    return s;
}

int main(int ac, char *argv[]){
    char *s = "hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789hijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char * ret = lengthOfLongestSubstring(s);
    printf("%s\n",ret);
}

