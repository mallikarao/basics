#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
    unsigned int a=1;
    unsigned int b=2;
    printf("Address of a: %p, b: %p\n", &a, &b);
    char *ptr= (char *)&a;
    printf("address of ptr: %p, value: 0x%x\n", ptr, *ptr);
    if(*ptr) printf("Little endian\n");
    else printf("Big Endian\n");
}
