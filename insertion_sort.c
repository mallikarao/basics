#include <stdio.h>
#include <stdlib.h>

void
insertion_sort(int a[], int n)
{
	int k, j, i, temp;
	for(k = 1; k < n; k++) {
		j = k;
		for(j = k; j>=0; j--) {
			printf("a[j] = %d\tkey = %d\n", a[j-1], a[j]);
			if(a[j] < a[j-1]) {
				//swap
				temp = a[j-1];
				a[j-1] = a[j];
				a[j] = temp;
			} // else break from this inner for loop for everything before this
            //is sorted
		}
	printf("The array is:\n");
        for(i=0; i<6; i++) {
                printf("%d\t", a[i]);
        }
	}	
}

int main(int argc, char **argv)
{
	int i;
	int a[6] = {0};
	printf("Enter the 6 elements for array\n");
	for(i=0; i<6; i++) {
		scanf("%d", &a[i]);
	}
	insertion_sort(a, 6);
}
