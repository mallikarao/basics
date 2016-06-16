#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
find_longest_word(char *str)
{
    char new[32]={};
    char largest[256]={};
    int i=0;
    int j=0;
    int low=0;

    while(i<strlen(str)) {
        if(strncmp(&str[i], " ", 1)==0) {
            for(j=low;j<i;j++) {
                new[j-low]=str[j];
            }
            new[j-low]='\0';
            if(strlen(new)>strlen(largest)) {
                strncpy(largest, new, strlen(new));
            }
            low=i+1;
            i=low;
        }
        i++;
    }
    // for the last word
    for(j=low;j<i;j++) {
        new[j-low]=str[j];
    }
    new[j-low]='\0';
    if(strlen(new)>strlen(largest)) {
        strncpy(largest, new, strlen(new));
    }
    printf("largest word: %s\n", largest);
}

int main(int argc, char **argv)
{
    char *str="argument seems to be the longest, butisitreallyhuh";
    printf("the length of the string is: %lu\n", strlen(str));
    find_longest_word(str);
    return (0);
}
