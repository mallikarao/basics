#include<stdio.h>
#include<stdlib.h>
//fix this algorithm
void max_heapify(int a[], int n, int i)
{
    int l = (2*i)+1;
    int r = (2*i)+2;
    int largest = 0;
    int temp = 0;

    if (l<n && a[l] > a[i]) {
        largest = l;
    } else {
        largest = i;
    }

    if(r<n && a[r]>a[largest]) {
        largest = r;
    }
    if (largest!=i) {
        temp=a[largest];
        a[largest]=a[i];
        a[i]=temp;
        max_heapify(a, n, largest);
    }
}

void build_max_heap(int a[], int n)
{
    int i=0;

    for(i=(n/2)-1;i>=0;i--) {
        max_heapify(a, n, i);
    }
    for(i=0;i<n;i++) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int a[6] = {0};
    int i=0;
    int temp=0;

    printf("Enter 6 elements\n");
    for(i=0;i<6;i++) {
        scanf("%d", &a[i]);
    }
    build_max_heap(a, 6);
    for(i=3;i>=0; i--) {
        temp=a[1];
        a[1]=a[i];
        a[i]=temp;
        max_heapify(a, 6, 1);
    }
}
