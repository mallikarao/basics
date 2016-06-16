#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int data = 2952790016;
    int num_bits = sizeof(unsigned int) * 8;
    printf("(data): 0x%x\n", data);
    int i = 0;
    int num1 = 0;
    int num2 = data;
    int rotate_by_this_much = 0;

    printf("Enter by how much you want to rotate: \n");
    scanf("%d", &rotate_by_this_much);
    
    for(i=1;i<=rotate_by_this_much;i++) {
        num1 = ((1<<(num_bits-1)) & num2) ? 1:0;
        printf("num1: 0x%x\t, num2: 0x%x\n", num1, num2);
        num2 = (num2<<1);
        printf("num1: 0x%x\t, num2: 0x%x\n", num1, num2);
        num2 = num1 | num2;
    }
    printf("rotated(data): 0x%x\n", num2);
    
    /*
    printf("the method2 rotate gives this: 0x%x\n",
        ((0xFE<<rotate_by_this_much)|(0xFE&(0xFF>>(num_bits-rotate_by_this_much)))));
    */
}
