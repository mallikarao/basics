#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
}

int main(int argc, char **argv)
{
    struct node *tree;
    int data;

    FILE *tree = fopen("ins_tree.txt", "r");

    while(fscanf(tree, "%d", &data)!=EOF) {
        insert(&tree, data);
        print_tree(tree);
    }

    return 0;
}

