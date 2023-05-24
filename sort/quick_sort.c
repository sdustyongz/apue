#include <stdio.h>
#include <stdlib.h>


int quick_move(int num[],int start ,int end){

    if(start >= end) return start;
    int r = num[end];
    int j = start;
    int pos = end;
    int temp;
    while(j < pos){
        if(num[j] >= r){
            temp = num[pos];
            num[pos] = num[j];
            num[j] = num[pos-1];
            pos --; 
        }else{
            j++;
        }
    }
    num[pos] = r;
    return pos;
}

void quick_sort(int num[],int start,int end){
    if(start>=end) return;
    int q = quick_move(num,start, end);
    quick_sort(num,start,q-1);
    quick_sort(num,q+1,end);    
}


int main(int argc, char *argv[]){
    int a[]  = {3,1,4,2};
    //jint pos = quick_move(a,0,3);
   // printf("pos is %d\n",pos);
    quick_sort(a,0,3);
    for(int i = 0;i < 4;i++){
        printf("%d\n", a[i]);
    }
    
}
