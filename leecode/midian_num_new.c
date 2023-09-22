#include <stdio.h>
#include <stdlib.h>
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{

    int total = nums1Size + nums2Size;
    if (total == 0)
        return 0.0;
    if (nums1Size == 0 || nums2Size == 0)
    {
        int *a;
        if (nums1Size > 0)
        {
            a = nums1;
        }
        else
        {
            a = nums2;
        }
        if ((total & 1) != 1)
        {
            return (a[total / 2] + a[total / 2 - 1]) / 2.0;
        }
        else
        {
            return a[total / 2];
        }
    }

    int mid = (total & 1 == 1) ? total / 2 + 1 : total / 2;
    int start1 = 0, start2 = 0;
    int index1 = (nums1Size ) / 2 - 1;
    int index2 = (nums2Size ) / 2 - 1;
    index1 = index1 < 0?0:index1;
    index2 = index2 < 0? 0 :index2;
    int count = mid;
    while (mid > 0)
    {
        int a = nums1[start1 + index1] - nums2[start2 + index2];
        if (a < 0)
        {
            start1 = start1 + index1 + 1;
            mid = (mid - index1) / 2;
            count -= (index1 + 1);
            if(mid == 0){
                index1 = 0;
                index2 = 0;
                break;
            }
            if (start1 + mid >= nums1Size)
            {
                index1 = nums1Size - start1 - 1;
            }
            else
            {
                index1 = mid - 1;
            }
            if (start2 + mid >= nums2Size)
                index2 = nums2Size - start2 - 1;
            else
                index2 = mid - 1;
        }
        else
        {
            start2 = start2 + index2 + 1;
            mid = (mid - index2) / 2;
            count -= (index2 + 1);
            if(mid == 0){
                index1 = 0;
                index2 = 0;
                break;
            }
            if (start2 + mid >= nums2Size)
            {
                index2 = nums2Size - start2 - 1;
            }
            else
            {
                index2 = mid - 1;
            }
            if (start1 + mid >= nums1Size)
                index1 = nums1Size - start1 - 1;
            else
                index1 = mid - 1;
        }

        if (mid < 1)
        {
            break;
        }
    }

    int left, right;
    if (nums2[start2 + index2] < nums1[start1 + index1])
    {
        if (count == 2)
        {
            left = nums1[start1 + index1];
            index1++;
        }
        else if (count == 1)
        {
            left = nums2[start2 + index2];
            index2++;
        }
    }
    else
    {
        if(count == 2){
        left = nums2[start2 + index2];
        index2++;
        } else{
            left = nums1[start1 + index1];
            index1++;
        }
    }
    if ((total & 1) != 1)
    {
        if (start1 + index1 >= nums1Size)
            right = nums2[start2 + index2];
        else if (start2 + index2 >= nums2Size)
            right = nums1[start1 + index1];
        else
        {
            right = nums1[start1 + index1];
            if (right > nums2[start2 + index2])
                right = nums2[start2 + index2];
        }
        return (left + right) / 2.0;
    }
    return left;
}

int main(int argc, char *argv[])
{
    int a[] = {1,3};
    int b[] = {2};
    double c = findMedianSortedArrays(a, 2, b, 1);
    printf("%f\n", c);
}