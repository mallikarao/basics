#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    void *p = malloc(4);
    int *q = malloc(4);
    printf("the contents in p: %p\n", p);
    printf("the contents in p: %p\n", q);
    p++;
    q++;
    printf("the contents in p: %p\n", p);
    printf("the contents in p: %p\n", q);
}
