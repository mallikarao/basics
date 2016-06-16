#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int
append_lists(struct node **head1, struct node **head2)
{
    if(!*head1) {
        *head1 = *head2;
        return 0;
    }

    struct node *cur = *head1;
    while(cur->next!=NULL) {
        cur=cur->next;
    }
    cur->next = *head2;
    *head2 = NULL;
    return 0;
}

int
delete_matching_elements(struct node **head, int key)
{
    struct node *cur = *head;
    struct node *temp = NULL;

    if(!(*head)) {
        return -1;
    }

    //deleting at head
    while((*head)->data == key) {
        *head = cur->next;
        temp = cur;
        cur=cur->next;
        free(temp);
        temp=NULL;
    }
 
    while(cur!=NULL && cur->next!=NULL) {
        if(cur->next->data == key) {
            temp = cur->next;
            cur->next = cur->next->next;  
            free(temp);
            temp = NULL;
        } else {
            cur=cur->next;
        }
    }
    return 0;
}

int
insert_nth_node(struct node **head, int index, int data) {
    
    struct node *temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    struct node *cur = *head;

    if(index == 1) {
        printf("Inserting %d at head\n", data);
        temp->next = *head;
        *head = temp;
        return 0;
    }

    int i = 1;
    // Fix this
    while(cur->next!=NULL && i<(index-1)) {
        i++;
        cur=cur->next;
    }
    printf("In the end, %d\n", cur->data);
    if(cur->next == NULL) {
        printf("Inserting %d at tail, %d out of range\n", data, index);
        cur->next = temp;
        temp->next = NULL;
    } else {
        printf("Inserting %d at %d position\n", data, index);
        temp->next = cur->next;
        cur->next = temp;
    }
    return 0;
}

int
count(struct node *head)
{
    struct node *cur = head;
    int count = 0;

    while(cur!=NULL) {
        count++;
        cur = cur->next;
    }
    printf("Count of linked_list: %d\n", count);
    return 0;
}

int
delete_nth_node(struct node **head, int n)
{
    struct node *cur = *head;
    struct node *prev = *head;
    int i = 1;

    //delete the first node
    if(n == 1) {
        printf("Deleting first node\n");
        struct node *temp = cur;
        cur = cur->next;
        free(temp);
        *head = cur;
        return 0;
    }
    
    while(i < n && cur!=NULL) {
        prev = cur;
        cur=cur->next;
        i++;
    }
    if(cur) {
        printf("Deleting %d element: %d\n", i, cur->data);
        prev->next = cur->next;
        free(cur);
        cur = NULL;
        return 0;
    } else {
        printf("Out of range\n");
        return -1;
    }
}

struct node *
get_nth_node(struct node* head, int n)
{
    int i = 1;
    struct node *cur = head;

    while(i < n && cur != NULL) {
        cur=cur->next;
        i++;
    }
    if (cur) {
        printf("The %dth element is: %d\n", i, cur->data);
    } else {
        printf("Out of range\n");
    }
    return (cur);
}

int
delete_from_head(struct node **head)
{
    if(!(*head)) {
        return -1;
    }

    struct node *temp = *head;

    *head = (*head)->next;

    free(temp);
    temp = NULL;
    return 0;
}

void
print_list(struct node *head)
{
    if(!head) {
        printf("----\n");
    }
    struct node *cur = head;
    while(cur!=NULL){
        printf("%d\t", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int
insert_into_head(struct node **head, int data)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
  
    if(*head == NULL) {
        *head = temp;
        return 0;
    }
    temp->next = *head;
    *head = temp;
    return 0;
}

int main(int argc, char **argv)
{
    struct node *list;
    struct node *list2;
    int data = 0;

    print_list(list); 
    FILE *linked_list = fopen("linked_list.txt", "r");

    if(!linked_list) {
        printf("File open error on linked_list.txt");
    }
    
    while(fscanf(linked_list, "%d", &data) != EOF) {
        insert_into_head(&list, data);
        insert_into_head(&list2, data);
        print_list(list);
    }
    count(list);
    delete_from_head(&list);
    print_list(list);
    
    get_nth_node(list, 4);
    get_nth_node(list, 100);
    
    delete_nth_node(&list, 4);
    delete_nth_node(&list, 1);
    delete_nth_node(&list, 40);
    print_list(list);
    
    insert_nth_node(&list, 2, 87);
    insert_nth_node(&list, 4, 87);
    print_list(list);
    insert_nth_node(&list, 87, 87);
    print_list(list);
    insert_nth_node(&list, 1, 87);
    insert_nth_node(&list, 1, 87);
    print_list(list);
    delete_matching_elements(&list, 87);
    printf("After delete_matching_elements\n");
    print_list(list);
    
    count(list);
    struct node *list3 = NULL;
    append_lists(&list3, &list);
    printf("Appending list3=(NULL, list), printing list3\n");
    print_list(list3);
    
    list3 = NULL;
    append_lists(&list, &list3);
    print_list(list);
    
    append_lists(&list, &list2);
    printf("Came here\n\n");
    print_list(list);
    count(list);
}

