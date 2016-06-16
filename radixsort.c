#include <stdio.h>
#include <stdlib.h>

// This program has hardcoded the digits to be 3, so, pls enter numbers which
// can be represented in 3 digits, i.e. 0-7. digit=ciel(log to base 2 of the
// largest number.

#define base 2

struct item {
    int num;
    int bit;
};

struct item b[5] = {0};

void
counting_sort(struct item b[], int n, int shift)
{
    int i=0;
    int j=0;

    for(i=0;i<n;i++) {
        b[i].bit = (b[i].num)&(0x1<<shift)? 1: 0;
    }
    
    // find the largest b[i].bit among all poss values of
    // b[i].bit
    // here, that number is 2

    int c[base] = {0};

    for(i=0;i<n;i++) {
        (c[b[i].bit])++;
    }
    for(j=0;j<base;j++) {
        printf("%d\t", c[j]);
    }
    printf("\n");

    for(j=1;j<base;j++) {
        c[j]+=c[j-1];
    }
    for(j=0;j<base;j++) {
        printf("%d\t", c[j]);
    }
    printf("\n");

    struct item d[5] = {0};
    i = 0;
    for(i=(n-1);i>=0;i--) {
        d[c[b[i].bit]-1].bit = b[i].bit;
        d[c[b[i].bit]-1].num = b[i].num;
        (c[b[i].bit])--;
    }
    for(i=0;i<n;i++) {
        b[i].bit = d[i].bit;
        b[i].num = d[i].num;
        printf("b[i].bit: %d, b[i].num: %d\n", b[i].bit, b[i].num);
    }
}

void
radix_sort(int a[], int n)
{
    int digits = 3; // hardcoded to 3 here. it is the ciel(log to base 2 of
    // largest).
    int i=0;

    for(i=0;i<n;i++) {
        b[i].num=a[i];
        b[i].bit = 0;
    }
    for(i=0;i<3;i++) {
        counting_sort(b, 5, i);
    }
}

int main(int argc, char **argv)
{
    int a[5];
    int i = 0;
    int largest;

    printf("Enter 5 elements\n");
    for(i=0;i<5;i++) {
        scanf("%d", &a[i]);
    }
    
    radix_sort(a, 5);
    printf("\n\nFinal sorted array: \n");
    for(i=0;i<5;i++) {
        printf("b[i].bit: %d, b[i].num: %d\n", b[i].bit, b[i].num);
    }
}
