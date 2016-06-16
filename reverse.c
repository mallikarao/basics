#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char a[8] = {'a','b','c','d','e','f','g'};
	char *b;
	b = malloc(sizeof(char) * 8);
	strncpy(b, "abc", 8);	
	printf("a:%s, \tb: %s\n", a, b);
	char *c = "hello world";
	printf("c: %s\n", c);
	int len = strlen(c);
	printf("strlen(c) : %d\n", len);
	char *d;
	d = malloc(strlen(c)*sizeof(char));
	int i;
	for(i=0; i<len; i++) {
		printf("c[%d]: %c\t", i, c[i]);
	}
	for(i=0; i<len; i++) {
		d[i] = c[(len-1)-i];
		printf("d[%d]: %c\t", i, d[i]);
	}
	d[len] = '\0';
	printf("d: %s\n", d);
}
