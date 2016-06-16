#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *s1 = NULL;
    char *s2 = NULL;
    
    s1=malloc(32);
    s2=malloc(32);
    printf("Enter 2 strings: s1 and s2, each no longer than 32 characters\n");
    scanf("%s", s1);
    scanf("%s", s2);

    int size1 = strlen(s1);
    int size2 = strlen(s2);

    char *temp = malloc(size1+1);
    strncpy(temp, s1, size1);
    temp[size1]= '\0';
    printf("temp after string copy of s1: %s\n", temp);
    strncat(temp, s1, size1);
    printf("temp after concatenation: %s\n", temp);

    const char *result = strstr(temp, s2);
    if(result == NULL) {
        printf("Not a substring\n");
        return (-1);
    }
    printf("The string s2: %s is a substring of string s1: %s\n", s2, s1);

    return (0);
}
