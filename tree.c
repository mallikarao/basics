#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *left;
    struct node *right;
    int data;
};

void print_tree(struct node *root)
{
	if(root) {
		print_tree(root->left);
		print_tree(root->right);
		printf("%d \t", root->data);
	}
}

void
search(struct node *tree, int key)
{
	if(!tree) {
		printf("Search complete, %d not found\n", key);
		return;
	}
	if(key == tree->data) {
		printf("%d present in the tree\n", key);
		return;
	}
	else if(key < tree->data) {
		search(tree->left, key);
	}
	else if(key > tree->data) {
		search(tree->right, key);
	}
}

void
delete(struct node **tree, int key)
{
        if(!(*tree)) {
                printf("Search complete, %d not found\n", key);
                return;
        }
        if(key == (*tree)->data) {
                printf("\n%d present in the tree\n", key);
                printf("Deleting %d\n", (*tree)->data);
		        // check if leaf node
                if ((*tree)->right == NULL && (*tree)->left ==  NULL) {
                	free(*tree);
			        *tree = NULL;
		        } else {
			        struct node *temp = *tree;
			        if ((*tree)->left) {
				        (*tree)->left->right = (*tree)->right;
				        (*tree) = (*tree)->left;
			        } else {
				        (*tree) = (*tree)->right;
			        }
                    /*
                    if((*tree)->right && (*tree)->left) 
                    */
			        free(temp);
                    temp = NULL;
                }
                return;
        } else if(key < (*tree)->data) {
                delete(&(*tree)->left, key);
        } else if(key > (*tree)->data) {
                delete(&(*tree)->right, key);
        }
}

void
insert_tree(struct node **tree, int data)
{
// check if the tree is empty
if(*tree == NULL) {
	struct node *temp = malloc(sizeof(struct node));
	temp->left = NULL;
	temp->right = NULL;
	temp->data = data;
	printf("Trying to insert %d\n", data);
	*tree = temp;
	return;
}
	//maybe it should be <=
    if(data < (*tree)->data) {
		insert_tree(&(*tree)->left, data);
	} else if(data > (*tree)->data) {
		insert_tree(&(*tree)->right, data);
	}
}

int main(int argc, char **argv)
{
    	struct node* root;
 	int i, data;	
	FILE *ins_file = fopen("ins_tree.txt", "r");
	if (!ins_file) {
		printf("Could not open the file to insert\n");
	}

	while(!feof(ins_file)) {
		fscanf(ins_file, "%d", &data);
		insert_tree(&root, data);
	}

    print_tree(root);
    printf("\n");
	search(root, 8);
	search(root, 55);
	search(root, 111);
	printf("\n");
	
	FILE *del_file = fopen("del_tree.txt","r");
	if(!del_file) {
		printf("File not found to delete\n");
	}
	while(!feof(del_file)) {
		fscanf(del_file, "%d", &data);
		delete(&root, data);
		print_tree(root);
	}
	return (0);
}
