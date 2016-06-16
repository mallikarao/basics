#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node*
build(int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->left=NULL;
    temp->right=NULL;
    temp->data = data;
    return temp;
}

void
print(struct node* root)
{
    if (root) {
        printf("%d\t", root->data);
        print(root->left);
        print(root->right);
    }
}

void
insert(struct node **root, int data)
{
    struct node *temp = build(data);
    if(*root==NULL) {
        *root = temp;
        return;
    }
    if(data<(*root)->data) {
        insert(&(*root)->left, data);
    } else if(data > (*root)->data) {
        insert(&(*root)->right, data);
    }
}

void
delete_tree(struct node **root)
{
    if(*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        free(*root);
        *root = NULL;
    }
}
struct node*
search(struct node **root, int data)
{
    if(!(*root)) {
        return NULL;
    }
    if(data < (*root)->data){
        search(&(*root)->left, data);
    } else if(data > (*root)->data) {
        search(&(*root)->right, data);
    } else if(data ==  (*root)->data) {
        return (*root);
    }
}

int main(int argc, char **argv) {
    struct node *root = build(2);
    struct node *found = NULL;
    
    root->left = build(1);
    root->right = build(3);
    insert(&root, 10);
    insert(&root, 7);
    print(root);
    found = search(&root, 3);
    if(found != NULL)
        printf("found the key: %d\n", found->data);
    delete_tree(&root);
    print(root);
}
