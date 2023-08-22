#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  bag_select(int weight[],int value[],int size,int bag_capacity){
    int dp_arr[size][bag_capacity];
    int i ,j,index;
    for(i = 0;i < size;i++){
        dp_arr[i][0] = 0;
    }
    for(j = 0;j < bag_capacity ;j++){
        dp_arr[0][j] = 0;
    }

    for(i = 1;i < size;i++){
        for(j = 1;j < bag_capacity;j++){
            index = j - weight[j-1];
            index = index >= 0 ? index:0;
            if(dp_arr[i-1][j] > (dp_arr[i-1][index] + value[j-1])){
                dp_arr[i][j] = dp_arr[i-1][j];
            }else{
                if(weight[j-1] < j)
                    dp_arr[i][j] =  dp_arr[i-1][index] + value[j-1];
                else dp_arr[i][j] = 0;
            }
        }
    }
    
    for(i = 0;i < size;i++){
        for(j = 0;j < bag_capacity; j++){
            printf("%d   ",dp_arr[i][j]);
        }
        printf("\n");
    }

}


int  main(int argc, char *argv[]){
    int weight[] = {4,1,9,3,5};
    int value[] = {10,3,4,5,1};
    bag_select(weight,value,5,13);
}