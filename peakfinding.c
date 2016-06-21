/* This program finds 'a' peak in a given array. if a[n]>a[n+1] and a[n]>a[n-1]; then a[n] is a peak
 * This program takes a recursive approach to solving it. 
 */

#include <stdio.h>
#include <stdlib.h>
/*
 * Return element if found and -1 if not found
 */
int findpeak(int a[], int low, int high){
    int mid = (low+high)/2;

    printf("low: %d, mid: %d, high:%d\n", low, mid, high);
    if(a[mid] < a[mid-1]){
        printf("LOW\n");
        return findpeak(a, low, mid);
    }else if(a[mid] < a[mid+1]){
        printf("HIGH\n");
        return findpeak(a, mid, high);
    }
    printf("mid: %d, a[mid]: %d\n", mid, a[mid]);
    return mid;
}


int main(int argc, char **argv) {
    int a[10] = {9,3,1,2,4,6,0,5,8,7};
    int i = 0;
    int len_array = (sizeof(a)/sizeof(int));
    while(i<10){
        printf(" %d,", a[i]);
        i++;
    }
    printf("\n");
    printf("size of array: %d", len_array);
    int peak = findpeak(a, 0, (len_array-1));
    printf("One of the peaks in the array is: %d\n", a[peak]);
    exit(0);
}
