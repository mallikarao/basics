#include <stdio.h>
#include <stdlib.h>

void
toggle_func(int a, int toggle)
{
    int num_bits = sizeof(int) * 8;
    
    if(!((1<<toggle)&a)) {
        a= a|(1<<toggle);
    } else a=a&(~(1<<toggle));
    printf("After toggling: %d\n", a);
}

void
alt_toggle(int a, int toggle)
{
    int num_bits = sizeof(int)*8;
    printf("Before toggling: %d\n", a);

    a=a^(1<<toggle);
    
    printf("After toggling: %d\n", a);
}

int main(int argc, char **argv)
{
    int a = 7;
    int b=5;
    int toggle = 1;
    toggle_func(b, toggle);
    toggle_func(a, toggle);
    alt_toggle(a, toggle);
    alt_toggle(b, toggle);
}

// when ever you want to toggle, use XOR/^ and a good control number
// for eg. to toggle all bits, XOR with 0xFFFF
