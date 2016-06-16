#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1

bool
isthisbitset(int a, int k) {
	printf("isthisbitset: %d \t a:%d\t k: %d\n", (a & (1<<k)), a, k);
	return ( a & (1<<k) )? TRUE:FALSE;
}


int 
is_palindrome(int a) {
	int num_bits = 8*sizeof(unsigned int);
        printf("There are %d bits in a: %d\n", num_bits, a);

	int left = num_bits-1;
	int right = 0;
	
	while (left > right) {
		if(isthisbitset(a, left) != isthisbitset(a, right)) {
			printf("Not a palindrome\n");
			return FALSE;
		}
		left --;
		right ++;
	}
	printf("The number dec(a): %d, hex(a): 0x%x is a palindrome\n", a, a);
	return TRUE;
}


int main(int argc, char **argv)
{
	void *ptr;
	unsigned int a = ((1<<1)+ (1<<15) + (1<<16));
	unsigned int b = ((1<<15) + (1<<16));
	ptr= &a;
	printf("(hex)a = 0x%x\n", a);
	printf("arch is a %lu bit machine\n", 8*sizeof(ptr));
	int ret;
	is_palindrome(a);
	is_palindrome(b);
}	
