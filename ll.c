#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *reverse_head= NULL;

//This is if the list contains consecutive duplicates
int
remove_duplicates(struct node **head)
{
    struct node *remove = NULL;
    struct node *cur = *head;

    // if there are duplicates at the head of the list
    while((*head) && (*head)->next && (*head)->data == (*head)->next->data) {
        remove = (*head)->next;
        (*head)->next = (*head)->next->next;
        free(remove);
        remove = NULL;
    }
    // well, now that we are done removing duplicates at head, let's move on
    while(cur!=NULL && cur->next!=NULL) {
        if(cur->data == cur->next->data) {
            remove = cur->next;
            cur->next = cur->next->next;
            free(remove);
            remove = NULL;
        } else {
            cur=cur->next;
        }
    }
    return 0;
}

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
    while(*head && (*head)->data == key) {
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

void
reverse_recurse(struct node **head, struct node **headref)
{
    print_list(*head);
    if((*head)==NULL) {
        return;
    }
    
    reverse_recurse(&(*head)->next, headref);
    
    if((*head)->next==NULL) {
        *headref = *head;
        reverse_head = *headref;
    } else {
        (*headref)->next = *head;
        (*headref) = (*headref)->next;
        (*headref)->next = NULL;
    }
    printf("Printing revsered list:\n");
    print_list(reverse_head);
    return;
}

struct node *
reverse(struct node *head)
{
    if(!head) {
        return NULL;
    }
    struct node *reverse_list =NULL;
    struct node *cur = head;

    while(cur!=NULL) {
        insert_into_head(&reverse_list, cur->data);
        // temp=cur; cur=cur->next; free (temp)
        cur=cur->next;
    }
    return (reverse_list);
}

int
insert_at_tail(struct node **head, int data)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if(*head == NULL) {
        *head = temp;
        return 0;
    }
    struct node *cur = *head;

    while(cur->next!=NULL) {
        cur=cur->next;
    }
    cur->next = temp;
    return 0;
}

int
sorted_merge(struct node **head1, struct node **head2)
{
    if(*head1 == NULL) {
        *head1 = *head2;
        return 0;
    }
    if(*head2 == NULL) {
        return 0;
    }
    // we come here only if we surely have two non-empty lists
    struct node *cur1 = *head1;
    struct node *cur2 = *head2;
    struct node *mergelist = NULL;
    struct node *remove = NULL;

    while(cur1!=NULL && cur2!=NULL) {
        if (cur1->data <= cur2->data) {
            insert_at_tail(&mergelist, cur1->data);
            remove = cur1;
            cur1=cur1->next;
        } else if(cur2->data < cur1->data) {
            insert_at_tail(&mergelist, cur2->data);
            remove = cur2;
            cur2=cur2->next;
        }
        free(remove);
        remove = NULL;
    }
    if (cur1) {
        while(cur1!=NULL) {
            insert_at_tail(&mergelist, cur1->data);
            //remove= cur;
            cur1=cur1->next;
            // free(remove);
        }
    } else if(cur2) {
        while(cur2!=NULL) {
            insert_at_tail(&mergelist, cur2->data);
            //remove=cur;
            cur2=cur2->next;
            //free(remove);
        }
    }
    *head1 = mergelist;
    free(*head2);
    return 0;
}

int
sorted_insert(struct node **head, int data)
{
    struct node *cur = *head;
    struct node *temp = malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;

    if(data < (*head)->data) {
        temp->next = *head;
        *head = temp;
        return 0;
    }
    while(cur!=NULL && cur->next!=NULL && cur->next->data < data) {
        cur=cur->next;
    }
    if (cur) {
        temp->next = cur->next;
        cur->next = temp;
    }
    return 0;
}

int
sort_linked_list(struct node **head)
{
    struct node *sort_list = NULL;
    struct node *comp, *delete_this_node;
    int highest = 0;
    struct node *cur = *head;

    while (cur->next!=NULL) {
        highest = cur->data;
        delete_this_node = cur;
        comp = cur->next;
        while(comp!=NULL) {
            if (comp->data > highest) {
                highest = comp->data;
                delete_this_node = comp;
            }
            comp=comp->next;
        }
        insert_into_head(&sort_list, highest);
        delete_matching_elements(&(*head), delete_this_node->data);

        cur=*head;
        print_list(*head);
    }
    insert_into_head(&sort_list, cur->data);
    // delete_matching_elements(&(*head), delete_this_node->data); 
    printf("Sorted list\n");
    print_list(sort_list);
    *head = sort_list;
    return 0;
}

int
main(int argc, char **argv)
{
    struct node *list;
    struct node *list2;
    int data = 0;
    struct node *list6;
    struct node *list7;

    print_list(list); 
    FILE *linked_list = fopen("linked_list.txt", "r");
    FILE *sorted_list1 = fopen("sorted_list1.txt", "r");
    FILE *sorted_list2 = fopen("sorted_list2.txt", "r");
    
    if(!linked_list || !sorted_list1 || !sorted_list2) {
        printf("File open error on one of the input files.\n");
    }
    
    while(fscanf(linked_list, "%d", &data) != EOF) {
        insert_into_head(&list, data);
        insert_into_head(&list2, data);
        print_list(list);
    }
    insert_at_tail(&list, 101);
    print_list(list);
    while(fscanf(sorted_list1, "%d", &data) != EOF) {
        insert_into_head(&list6, data);
    }
    printf("list6: \n");
    print_list(list6);

    while(fscanf(sorted_list2, "%d", &data) != EOF) {
        insert_into_head(&list7, data);
    }
    printf("list7: \n");
    print_list(list7);
    
    struct node *list8 = reverse(list7);
    printf("reverse of list7 looks like this:\n");
    print_list(list8);
    struct node *list9 =NULL;
    reverse_recurse(&list8, &list9);
    print_list(reverse_head);
    
    printf("After sorted_merge of list6 and list7:\n");
    sorted_merge(&list6, &list7);
    print_list(list6);

    count(list);
    sort_linked_list(&list);
    sorted_insert(&list, 3);
    sorted_insert(&list, 103);
    print_list(list);
    sorted_insert(&list, 1);
    sorted_insert(&list, 1);
    sorted_insert(&list, 1);
    print_list(list);
    sorted_insert(&list, 90);
    print_list(list);
    sorted_insert(&list, 60);
    sorted_insert(&list, 60);
    sorted_insert(&list, 60);
    print_list(list);

    printf("Removing duplicates\n");
    remove_duplicates(&list);
    print_list(list);

    printf("Deleting from head\n");
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

    struct node *list4 = NULL;
    insert_into_head(&list4, 99);
    insert_into_head(&list4, 99);
    insert_into_head(&list4, 99);
    insert_into_head(&list4, 99);
    print_list(list4);
    delete_matching_elements(&list4, 99);
    printf("After list4 delete_matching_elements\n");
    print_list(list4);
    
    struct node *list5 = NULL;
    insert_into_head(&list5, 95);
    insert_into_head(&list5, 95);
    insert_into_head(&list5, 95);
    insert_into_head(&list5, 95);
    print_list(list5);
    remove_duplicates(&list4);
    printf("After list5 remove_duplicates\n");
    print_list(list5);

    struct node *list3 = NULL;
    append_lists(&list3, &list);
    printf("Appending list3=(NULL, list), printing list3\n");
    print_list(list3);
    
    list3 = NULL;
    append_lists(&list, &list3);
    print_list(list);
    
    append_lists(&list, &list2);
    print_list(list);
    count(list);
}

