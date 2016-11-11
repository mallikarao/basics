#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int s; 
    int t; 
    scanf("%d %d",&s,&t);
    int a; 
    int b; 
    scanf("%d %d",&a,&b);
    int m; 
    int n; 

    int result_apples = 0;
    int result_oranges = 0;
    
    scanf("%d %d",&m,&n);
    int *apple = malloc(sizeof(int) * m);
    for(int apple_i = 0; apple_i < m; apple_i++){
       scanf("%d",&apple[apple_i]);
    }
    int *orange = malloc(sizeof(int) * n);
    for(int orange_i = 0; orange_i < n; orange_i++){
       scanf("%d",&orange[orange_i]);
    }
    for(int i=0;i<n;i++){
            if(orange[i] < 0 && (orange[i]-orange[i]-orange[i])>= (b-t) && (orange[i]-orange[i]-orange[i]) <= (b-s)){
                result_oranges++;
         }
    }

    for (int j=0;j<m;j++){
        if(apple[j] > 0 && apple[j] <= (t-a) && apple[j] >= (s-a)){
            result_apples++;
        }
    }

    printf("%d\n", result_apples);
    printf("%d\n", result_oranges);
    return 0;
}

