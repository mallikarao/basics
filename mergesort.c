#include <stdio.h>
#include <stdlib.h>

void
merge(int a[], int low, int mid, int high)
{
    int i = low;
    int j = mid+1;
    int k = 0;
    int b[high+1];

    while(i<=mid && j<=high) {
        if(a[i]<=a[j]) {
            b[k]=a[i];
            i++;
        } else {
            b[k]=a[j];
            j++;
        }
        k++;
    }
    while(i<=mid) {
        b[k]=a[i];
        i++;
        k++;
    }
    while(j<=high) {
        b[k]=a[j];
        k++;
        j++;
    }
    k--;
    while(k>=0) {
        a[low+k] = b[k];
        printf("%d\t", a[k]);
        k--;
    }
    printf("\n");
}


void
merge_sort(int a[], int low, int high)
{
    if(low<high) {
        int mid = (low+high)/2;
        
        merge_sort(a, low, mid);
        merge_sort(a, mid+1, high);
        merge(a, low, mid, high);
    }
}

int main()
{
    int a[10];
    int i = 0;

    //input the array
    for(i=0;i<10;i++) {
        scanf("%d", &a[i]);
    }
    for(i=0;i<10;i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");

    merge_sort(a, 0, 9);
    for(i=0;i<10;i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}
