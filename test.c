#include <stdio.h>
#include <stdlib.h>

int squared(volatile int *ptr) {
    printf("%d\n", (*ptr * *ptr)); 
    return (*ptr * *ptr);
}
    
int main(int argc, char **argv) {
    int a = 6;
    int ret;
    ret = squared(&a);
    printf("ret: %d\n", ret);
}
