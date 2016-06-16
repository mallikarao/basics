#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOW 0
#define HIGH(x)	(x-1)

void swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void gen_permutation(char *str, int low, int high) 
{
	int j; 
   	if (low == high)
     		printf("%s\n", str);
   	else
   	{
        	for (j = low; j <= high; j++) {
          		swap((str+low), (str+j));
          		gen_permutation(str, low+1, high);
          		swap((str+low), (str+j));
       		}
   	}
}

int main(int argc, char **argv)
{
   	char str[5] = "wxyz";
	printf("The reference string is: %s\n\n", str); 
   	int len = strlen(str);
	gen_permutation(str, LOW, HIGH(len));
   	return (0);
}
