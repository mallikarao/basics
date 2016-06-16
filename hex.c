#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    signed int a = -1;

    printf("hex(a) = %x\n", a);
    
    int complement = !a;
    printf("hex(a) = %x\n", complement);
}
