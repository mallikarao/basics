#include <stdio.h>
#include <stdlib.h>

struct tree {
    int data;
    struct tree *left;
    struct tree *right;
};

struct stack {
    struct tree *treenode;
    struct stack *next;
};


int
isempty(struct stack *topref)
{
    if(topref ==NULL) return 1;
    return 0;
}

void
push(struct stack **topref, struct tree *node)
{
    struct stack *cur = *topref;

    struct stack *new = malloc(sizeof(struct stack));
    new->treenode = node;
    new->next = *topref;
    *topref = new;
}

struct tree*
pop(struct stack **topref)
{
    struct stack *remove;
    struct tree *result;
    if(isempty(*topref)) {
        return NULL;    
    } else {
    remove = *topref;
    result = remove->treenode;
    *topref=(remove)->next;
    free(remove);
    remove=NULL;
    return (result);
    }
}

void
print(struct tree *root)
{
    struct tree *cur = root;

    int done = 0;
    struct stack *stack = NULL;

    while (!done) {
        if(cur) {
            //printf("%d\t", cur->data);
            push(&stack, cur);
            cur=cur->left;
        } else if(isempty(stack)) {
            done = 1;
        } else {
            cur = pop(&stack);
            printf("%d\t", cur->data);
            cur = cur->right;
        }
    }
    printf("\n");
}

/*
void
delete(struct tree **root, int data)
{
    // Note: it does not work for any right trees which do not have a left sub
    // part. Does not work fr root

    // is the node root
    struct tree *cur = *root;
    struct tree *prev=NULL;

    int done = 0;
    struct stack *stack = NULL;

    while (!done) {
        if(cur) {
            push(&stack, cur);
            cur=cur->left;
        } else if(isempty(stack)) {
            done = 1;
        } else {
            cur = pop(&stack);
            if(cur->data == data) {
                printf("Deleting %d\n", cur->data);
                prev = pop(&stack);
             
                if(cur->right==NULL && cur->left) {
                    // pop another time into prev
                    // check if prev->right->data == cur->data or
                    // prev->left->data==cur->data
                    // delete cur and adjust the right pointer of prev
                    // push back prev to stack
                    printf("#### Right is NULL, left is NOT\n");
                    printf("prev->data: %d\n", prev->data);
                    if(prev->left->data==cur->data) {
                        prev->left = cur->left;
                        free(cur);
                    } else {
                        prev->right = cur->left;
                        free(cur);
                    }
                } else if(cur->left==NULL && cur->right) {
                    printf("#### Left is NULL, right is NOT\n");
                    printf("prev->data: %d\n", prev->data);
                    if(prev->left->data==cur->data) {
                        prev->left = cur->right;
                        free(cur);
                    } else {
                        prev->right = cur->right;
                        free(cur);
                    }
                } else if(cur->right!=NULL && cur->left!=NULL) {
                    printf("#### Right and left are NON NULL\n");
                    printf("prev->data: %d\n", prev->data);
                    if(prev->left->data==cur->data) {
                        prev->left = cur->right;
                        prev->left->left = cur->left;
                        free(cur);
                    } else {
                        prev->right = cur->right;
                        prev->right->left = cur->left;
                        free(cur);
                    }
                } else {
                    printf("#### Right and left are NULL\n");
                    if(prev==NULL) {
                        printf("Prev is NULL, cannot delete last node\n");
                        break;
                    } else {
                    printf("prev->data: %d\n", prev->data);
                    
                    if(prev->left->data==cur->data) {
                        prev->left = NULL;
                    } else {
                        prev->right = NULL;
                    }
                    }
                    free(cur);
                }
                push(&stack, prev);
                cur=prev;
                }
            cur = cur->right;
            }
    }
    printf("\n");
}*/

struct tree*
minvaluenode(struct tree *root)
{
    struct tree *cur = root;
    while(cur->left!=NULL) {
        cur=cur->left;
    }
    return cur;
}

struct tree *
delete_recursive(struct tree *root, int data)
{
    if(root==NULL) return root;
    
    if(data < root->data) {
        root->left = delete_recursive((root)->left, data);
    } else if(data > (root)->data) {
        root->right = delete_recursive((root)->right, data);
    } else {
        // data is root, we need to delete root
        if(root->left==NULL) {
            struct tree *temp = root;
            root=root->right;
            free(temp);
            return(root);
        } else if(root->right==NULL) {
            struct tree *temp = root;
            root=root->left;
            free(temp);
            return(root);
        }
            struct tree* temp = minvaluenode(root->right);
            root->data=temp->data;
            root->right = delete_recursive(root->right, temp->data);
    }
    return root;
}

int
insert(struct tree **root, int data)
{
    struct tree *new = malloc(sizeof(struct tree));
    new->data = data;
    new->left = new->right = NULL;
    
    struct tree *cur = *root;
    struct tree *prev;

    if(!cur) {
        *root = new;
        return 0;
    }
    while(cur!=NULL) {
        prev = cur;
        if(data > cur->data) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    if(data>prev->data)
        prev->right=new;
    else
        prev->left=new;
    return 0;    
}

int main(int argc, char **argv) {
    struct tree *root = NULL;
    int ele = 0;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 2);
   
    FILE *ins_tree = fopen("ins_tree.txt","r");
    
    while(fscanf(ins_tree, "%d", &ele) != EOF) {
        insert(&root, ele);
    }

    print(root);
    delete_recursive(root, 10);    
    print(root);
    return 0;
}
