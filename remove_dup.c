#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *
sort_the_string(char *str)
{
    char temp;
    int i=0;
    int j=0;
    printf("Coming here\n\n");
    for(i=0;str[i];i++)
    {
        for(j=i+1;str[j];j++)
        {
            if(str[j]<str[i])
            {
                temp=str[j];
                str[j]=str[i];
                str[i]=temp;
            }
        }
    }
    printf("The sorted str: %s\n", str);
    return(str);
}

void
remove_dup(char *str)
{
    char *sorted_str = malloc(strlen(str));
    sorted_str = sort_the_string(str);
    printf("the sorted_str: %s\n", sorted_str);
    //delete_dup(sorted_str);
}

int main(int argc, char **argv)
{
    char *str="dcba";

    remove_dup(str);
    return (0);
}
