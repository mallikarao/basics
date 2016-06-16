#include <stdio.h>
#include <stdlib.h>

int binary_search(int *a, int key, int high)
{
    int low, mid;
    low=0;
    
    printf("Trying to find %d in:\n", key);
    while(low<=high) {
        mid=(low+high)/2;
        printf("a[mid] = %d\n", a[mid]);
        if(key==a[mid]) {
            printf("found %d in position: %d", key, mid);
            return mid;
        } else if(key<a[mid]) {
            high=mid;
        } else if(key>a[mid]) {
            low=(mid+1);
        }
    }
    // if we came till here then we did not find the key in the array
    printf("We did not find the key in the array\n");
    return (-1);
}


int main(int argc, char **argv)
{
    int *array;
    int num_elements;
    int i, key;

    printf("Enter the number of elements you want in the array\n");
    scanf("%d", &num_elements);
    array = malloc(sizeof(int) * num_elements);
    
    // Input the array
    printf("Enter the elements of the array in sorted order:\n");
    for(i=0;i<num_elements;i++) {
        scanf("%d", &array[i]);
    }

    // Output the array we have
    printf("The array we have is:\n");
    for(i=0;i<num_elements;i++) {
        printf("%d\t", array[i]);
    }
    
    // Input the key to search
    printf("\nEnter the number you want to search\n");
    scanf("%d", &key);
    
    // Search if we find the key in the array we have
    int ret;
    ret = binary_search(array, key, (num_elements-1));
    printf("ret: %d\n", ret);
}
