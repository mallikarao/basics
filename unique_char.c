#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alpha {
    char a;
    int present;
};

int
is_present(char a, int len, struct alpha *match_table)
{
    int i = 0;
    for(i=0; i<len; i++) {
        if(a == match_table[i].a) {
            return i;
        }
    }
    return -1;
}

int
build_match_table(char *str)
{
    int i=0;
    struct alpha *match_alpha = malloc(sizeof(struct alpha)*strlen(str));
    int ret=0;

    for(i=0; i<strlen(str); i++) {
        ret = is_present(str[i], strlen(str), match_alpha);
        if(ret!=-1) {
            (match_alpha[ret].present)++;
        } else {
            match_alpha[i].a = str[i];
            (match_alpha[i].present)++;
        }
        // fix this. No need to check if match_alpha[i].present>1
        if(match_alpha[i].present>1||match_alpha[ret].present>1) {
            return -1;
        }
    }
    return 0;
}

void
is_string_unique(char *str)
{
    if (build_match_table(str) == -1)        
        printf("string not unique characters\n");
    else
        printf("String is unique characters\n");
}

int main(int argc, char **argv) {
    char *str = "helo";
    char *str2 = "hello";

    printf("string is : %s\t", str);
    is_string_unique(str);
    printf("string is : %s\t", str2);
    is_string_unique(str2);

    return(0);
}
