#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b) {
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(int argc, char **argv)
{
	char str[5] = "ABCD";
	char dest[5] = "ABCD";
	int i, j, k;
	int len = strlen(str);
	
	printf("The length of the string %s is %d\n", str, len);
	printf("%s\n", str); // this prints the original string once.

	for(i=0; i<len; i++) {
		char str[5] = "ABCD";
		swap(str+i, str+0);
		for(j=1; j<len; j++) {
			strcpy(dest, str);
			for(k=1; k<len; k++) {
				if(!(str[k] == str[j])) 
				{
					strcpy(dest, str);
					swap(dest+j, dest+k);
					printf("%s\n", dest);
				}	
			}
		}
	}
	
	return (0);
}
