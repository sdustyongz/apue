#include <stdlib.h>
#include <stdio.h>

int* quick_partition(int * nums1, int start1 ,int size1, int * nums2, int start2, int size2);

int*  find(int * nums1, int size1, int * nums2 ,int size2,int k,int start1,int start2){
    int* par_pos = quick_partition(nums1,start1,size1,nums2,start2,size2);
    int q = par_pos[0];
    int r = par_pos[1];
    if(q + r == k) return  par_pos;
    //nums1[q] > nums2[r]? nums1[q]:nums2[r];
    else if(q+r < k){
        free(par_pos);
       find(nums1,size1, nums2, size2,k-q-r,q,r); 
    }else{
        free(par_pos);
       find(nums1,q, nums2, r,k,start1,start2); 
    }
}

int* quick_partition(int * nums1, int start1 ,int size1, int * nums2, int start2, int size2){
    int midnum = 0;
    int j,midpos;
    int * retval = malloc(2*sizeof(int));
    if((size1-start1) > (size2 - start2)){
        midpos = (size1+start1-1)/2;
        midnum = nums1[midpos];
        j = start2;
        while(j < size2 && nums2[j] < midnum) j++;
        retval[0] = midpos;
        retval[1]  = j; 
    }else{
        midpos = (size2+start2-1)/2;
        midnum = nums2[midpos];
        j = start1;
        while(j < size1 && nums1[j] < midnum) j++;
        retval[0] = j;
        retval[1]  = midpos; 
    }
    return retval;
}
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int mid = (nums1Size+nums2Size)/2;
    int zero = (nums1Size+nums2Size)%2;
   int * rs = find(nums1,nums1Size,nums2,nums2Size,mid,0,0);
   int pos1= rs[0];
   int pos2 = rs[1];
   free(rs);
   if(pos1 >= nums1Size){
       if(zero) return nums2[pos2];
       else return (nums2[pos2]+nums2[pos2+1])/2.0;
   }else if(pos2 >= nums2Size){
       if(zero) return nums1[pos1];
       else return (nums1[pos1]+nums1[pos1+1])/2.0;
   }else{
    int a,b = 0;
        if(nums1[pos1] < nums2[pos2]) {
            a = nums2[pos2++];
            pos1++;
        }else{
            a = nums1[pos1++];
            pos2++;
        }
        if(zero ) return a;
        else{
            if(pos1 >= nums1Size) b = nums2[pos2];
            else if(pos2>=nums2Size) b = nums1[pos1];
            else{
                b = nums1[pos1];
                if(b > nums2[pos2]) b =nums2[pos2];
            }
            return (a+b)/2.0;
        }
   }
}

int main(int argc, char *argv[]){
    int a[] = {1,4,5,6};
    int b[] = {2,3,7,8};
    double c = findMedianSortedArrays(a,4,b,4);    

    printf("%f\n",c);
}