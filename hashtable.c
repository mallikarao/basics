#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct node {
    int data;
    struct node *next;
};

struct bucket {
    int num_nodes;
    struct node *next;
    int hash_index;
};

struct hash_table {
    struct bucket **hashbucket;
    int count;
};

//hashing function
int
hash(key)
{
	printf("Generating index: %d\n", (key%SIZE));
	return (key%SIZE);
}

void
print(struct hash_table *hashtable)
{
        int i;
        printf("Hashtable count: %d\n", hashtable->count);
        for(i = 0; i < SIZE; i++) {
                if(hashtable->hashbucket[i]) {
                        printf("num_nodes: %d\t key: %d\n", hashtable->hashbucket[i]->num_nodes, hashtable->hashbucket[i]->hash_index);
                }
        }
}

void
search(struct hash_table *hashtable, int data)
{
	printf("searching for %d\n", data);
	int index = hash(data);
	struct node *cur = hashtable->hashbucket[index]->next;
	
	int n = hashtable->hashbucket[index]->num_nodes;
	if(cur) {
		while(n != 0){
			printf("num_nodes to search: %d\n", n);
			printf("cur->data: %d\n", cur->data);
			if(cur->data == data) {
				printf("Found data %d, in bucket: %d\n", data, index);
				return;
			}
			cur = cur->next;
			n--;
		}
		printf("Did not find element %d in hashtable\n", data);
	}
	printf("No elements to search\n");
}

void
insert(struct hash_table *hashtable, int data) 
{
	int index = hash(data);
	printf("Inside insert\n");
	
        struct node *temp = malloc(sizeof(struct node));
        temp->data = data;
        temp->next = NULL;

	struct node *cur = hashtable->hashbucket[index]->next;
	if(hashtable->hashbucket[index]->next == NULL) {
		// if it is the first element with this index, then create a new bucket+ create a new temp, init bucket, init the temp and
		printf("#### First element being inserted\n");
		hashtable->hashbucket[index]->next = temp;
		(hashtable->hashbucket[index]->num_nodes)++;
		printf("Inserted %d\n", hashtable->hashbucket[index]->next->data);
		return;	
	}
	while(hashtable->hashbucket[index]->next->next != NULL) {
		hashtable->hashbucket[index]->next = hashtable->hashbucket[index]->next->next;
	}
	hashtable->hashbucket[index]->next->next = temp;
	(hashtable->hashbucket[index]->num_nodes)++;
	printf("Inserted %d\n", cur->data);
}

void
buckets_init(struct hash_table *hashtable)
{
	int i;
	for(i = 0; i < SIZE; i++) {
		hashtable->hashbucket[i] = (struct bucket *) malloc(sizeof(struct bucket));
		hashtable->hashbucket[i]->num_nodes = 0;
		hashtable->hashbucket[i]->hash_index = i;
		hashtable->hashbucket[i]->next = NULL;
	}
}

int main(int argc, char **argv)
{
	struct hash_table *hashtable;
	int i;
	hashtable = malloc(sizeof(struct hash_table));
	hashtable->count = SIZE;
	hashtable->hashbucket = malloc((hashtable->count) * sizeof(struct node));
	for(i = 0;i < SIZE; i++) {
		hashtable->hashbucket[i] = NULL;
	}
	buckets_init(hashtable);
	insert(hashtable, 5);
	insert(hashtable, 61);
	insert(hashtable, 42);
	insert(hashtable, 78);
	insert(hashtable, 98);
	insert(hashtable, 0);
	insert(hashtable, 33);
	insert(hashtable, 112);
	print(hashtable);
	
	insert(hashtable, 44);
	search(hashtable, 44);
	search(hashtable, 61);
	search(hashtable, 31);
}
