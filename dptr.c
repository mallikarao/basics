#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int a = 5;
	int *p = &a;
	int **q = &p;
	
	printf("a:%d, &a: %p\n", a, &a);
	printf("p: %p, &p: %p\n", p, &p);
	printf("q: %p, &q: %p\n", q, &q);
	
	printf("a using p: %d\n", *p);
	printf("a using q: %d\n", **q);
	
	printf("*q: %p\n", *q);
	printf("&(*q): %p\n", &(*q));
	return 0;
}
