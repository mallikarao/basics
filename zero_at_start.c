#include<stdio.h>
#include<stdlib.h>

void
push_zero(int *list, int count)
{
    int sentinal = 0;
    int i = 0;

    for(i=0;i<count;i++) {
        if(*(list+i)==0) {
            if(*(list+sentinal)!=*(list+i)) {
                int temp =  *(list+sentinal);
                *(list+sentinal) = *(list+i);
                *(list+i) = temp;
            }
            sentinal++;
        }
    }
    for(i=0;i<10;i++) {
        printf("%d\t", *(list+i));
    }
}

int main(int argc, char **argv)
{
    int count = 10;
    int *list = malloc(sizeof(int)*count);
    int i = 0;

    printf("Enter 10 elements\n");
    for(i=0;i<10;i++) {
        scanf("%d", list+i);
    }
    for(i=0;i<10;i++) {
        printf("%d\t", *(list+i));
    }
    printf("\n");
    push_zero(list, count);
}
