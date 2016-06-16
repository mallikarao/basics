#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
break_into_words(char *str)
{
    // our splitting character is "" space
    int i=0;
    int j=0;
    int low=0;
    //new will be our placeholder for the new word, however we do not store it
    //anywhere
    char new[16]={};
    //this while loop takes care of all words except the last one
    while(i<strlen(str)) {
        if(strncmp(&str[i], " ", 1)==0) {
            for(j=low;j<i;j++){
                new[j-low]=str[j];
            }
            new[(j-low)]='\0';
            printf("new: %s\n", new);
            low=i+1;
            i=low;
        }
        i++;
    }
    // this is for the last word in the string
    for(j=low;j<=i;j++){
        new[j-low]=str[j];
    }
    new[(j-low)]='\0';
    printf("new: %s\n", new);
}

int main(int argc, char **argv)
{
    char *str = "Hello how are you doing today, Sir";
    printf("The length of the string: %lu\n", strlen(str));
    break_into_words(str);
    return (0);
}
