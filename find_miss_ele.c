#include <stdio.h>
#include <stdlib.h>

int
method2(int a[], int n)
{
    int total1 = a[0];
    int total2 = 0;
    int i= 0;

    printf("method2 assumes that there is only one missing element in an array of consecutive elements\n");
    // 2+3+4+5+6+7+8+9+10+11
    for(i=1;i<n;i++) {
        total1 = total1+(a[0]+i);
    }
    printf("total1: %d\n", total1);
    // 2+3+4+6+7+8+9+10+11
    for(i = 0; i<(n-1);i++) {
        total2 = total2+a[i];
    }
    printf("total2: %d\n", total2);
    printf("missing element from method2: %d\n", total1-total2);
    return 0;
}

int main(int argc, char **argv)
{
    int found = 0;
    int a[10] = {2,3,4,6,7,8,9,10, 11, 12};
    int i = 0;

    for(i = 1; i < 10; i++) {
        if(a[i] - a[i-1] != 1) {
            found = 1;
            printf("The missing element is %d\n", (a[i]-1));
            break;
        }
    }
    if(!found)
        printf("No missing elment\n");
    method2(a, 10);
}
