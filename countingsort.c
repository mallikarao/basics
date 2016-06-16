#include <stdio.h>
#include <stdlib.h>

void
counting_sort(int a[], int n, int k)
{
    int c[k+1];
    int i =0;
    int j = 0;

    for(j=0;j<=k;j++) {
        c[j] = 0;
    }

    for(i=0;i<n;i++) {
        (c[a[i]])++;
    }
    for(j=0;j<=k;j++) {
        printf("%d\t", c[j]);
    }
    printf("\n");

    for(j=1;j<=k;j++) {
        c[j]+=c[j-1];
    }

    for(j=0;j<=k;j++) {
        printf("%d\t", c[j]);
    }
    printf("\n");

    // build the last array-output array b, same size as a

    int b[n];
    
    for(j=0;j<n;j++) {
        b[c[a[j]]-1] = a[j];
        (c[a[j]])--;
    }

    for(j=0;j<n;j++) {
        printf("%d\t", b[j]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int a[6] = {0};
    int largest= 0 ;
    int i = 0;

    printf("Enter 6 elements\n");
    for(i=0;i<6;i++) {
        scanf("%d", &a[i]);
    }
    printf("From the list, what was the largest element ?\n");
    scanf("%d", &largest);
    counting_sort(a, 6, largest);
}

// we need a new array to hold the count of each index.
// populate the c array with the count. 
// index: a[i], and c[i] holds the count(a[i])

