#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int a = 202;
	printf("dec(a)= %d, hex(a)=0x%x\n", a, a);
	
	printf("right most nibble is: 0x%x\nleft most nibble: 0x%x\n", (a & 0x0F), (a & 0xF0) >> 4);
	printf("After the swap, the number looks like this: hex(a):0x%x\n", (((a & 0x0F) << 4) | ((a & 0xF0) >> 4)));

    printf("right nibble: 0x%x, left nibble: 0x%x\n", (a&0x0F)<<4, a>>4);
    printf("Method 2. after swap hex(a)0x%x\n", a<<4|a>>4);
}
