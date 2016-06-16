#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int
print_list(struct node *head)
{
    struct node *cur = head;
    if(cur==NULL) {
        printf("empty list\n");
        return -1;
    }
    while(cur != NULL) {
        printf("%d\t", cur->data);
        cur = cur->next;
    }
    printf("\n");
    return 0;
}


int
insert_node_at_tail(struct node **head, int data)
{
    struct node *cur;
    cur = *head;
    
    // check if list is empty
    struct node *temp;
    temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
 
    if(!cur) {
        cur=temp;
        return 0;
    }
    
    while(cur->next != NULL) {
        cur=cur->next;
    }

    cur->next = temp;
    return 0;
}

int
insert_node_at_head(struct node **head, int data)
{
    struct node *temp;
    temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if(*head == NULL) {
        *head = temp;
    } else {
        temp->next = *head;
        *head = temp;
    }
    
    return 0;
}

struct node*
delete_matching_element(struct node **head, int ele)
{
    struct node *cur = *head;
    struct node *prev = *head;

    if(!cur) {
        printf("Empty List\n");
    }
    while(cur!=NULL) {
        if(cur->data == ele) {
            //check if cur is the head node
            if () {
            }
            //else this means that the ele is not at head
        }
        cur = cur->next;
    }
}

// assumption: there is only one missing element between two given numbers
// list is sorted
// list can contain multiple missing numbers

int
find_missing_element(struct node *head)
{
    struct node *cur = head;
    int found = 0;

    while((cur!=NULL) && (cur->next != NULL)) {
        if(((cur->next->data - cur->data) != 1)) {
            printf("Missing element: %d\n", ((cur->data)+1));
            found++;
        }
        cur=cur->next;
    }
    if(!found) printf("Found no missing element\n");
    return 0;
}

void
init_list(struct node *head)
{
   head = malloc(sizeof(struct node));
   head->data = 0;
   head->next = NULL;
}

int
length_of_list(struct node *head)
{
    struct node *cur=head;
    int count = 0;
    if(!cur) {
        printf("List is empty\n");
        return 0;
    }
    while(cur != NULL) {
        count++;
        cur=cur->next;
    }
    return count;
}

void
delete_list(struct node **head)
{
    struct node *cur = *head;
    struct node *temp;

    while(cur!=NULL) {
        temp = cur;
        printf("Deleting %d\t", temp->data);
        cur = cur->next;
        free(temp);
        temp = NULL;
    }
    *head = NULL;
}



int main(int argc, char **argv)
{
    struct node *head;
    init_list(head);
    print_list(head);
    insert_node_at_head(&head, 5);
    print_list(head);
    insert_node_at_tail(&head, 7);
    insert_node_at_tail(&head, 8);
    insert_node_at_head(&head, 4);
    insert_node_at_head(&head, 3);
    printf("After inserting at tail\n");
    print_list(head);

    printf("The length of list: %d\n", length_of_list(head)); 

    find_missing_element(head);
    delete_list(&head);
    print_list(head);
    return (1);
}
