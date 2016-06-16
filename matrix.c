#include <stdio.h>
#include <stdlib.h>

void
print_matrix(int **a) 
{
    int i=0;
    int j=0;

    for(i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

void
build_matrix(int **a)
{
    int i=0;
    int j=0;

    for(i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            scanf("%d", &a[i][j]);
        }
    }

}

void
set_matrix(int **a)
{
    int i=0;
    int j=0;
    int k = 0;
    int b[3][3] = {0};

    for(i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            if(a[i][j]==0) {
                for(k=0;k<3;k++) {
                    b[i][k] = b[k][j] = 0;
                }
                break;
            } else {
                b[i][j] = a[i][j];
            }
        }
    }
    for(i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            a[i][j] = b[i][j];    
        }
    }
}

int main(int argc, char **argv) {
    int **a = malloc(3*sizeof(int));
    int k=0;

    for(k=0;k<3;k++) {
        a[k] = malloc(sizeof(int));
    }

    build_matrix(a);
    print_matrix(a);
    set_matrix(a);
    print_matrix(a);
}
