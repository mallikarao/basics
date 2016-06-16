#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int *p = (int*)0x00040040;
    int *q = (int *)0x00040080;
    
    printf("p: %p\n, q: %p\n", p, q);
    printf("%d\n\n", *p);
    
    printf("%d\n\n", *p);
}
