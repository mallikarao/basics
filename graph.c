#include<stdio.h>
#include<stdlib.h>

struct node {
    int dst;
    struct node* next;
};

struct adj_list {
    struct node *head;
};

struct graph {
    int num_vert;
    struct adj_list *array;
};

void print_graph(struct graph *g)
{
    struct node* cur = NULL;
    printf("coming here\n");
    int i = 0;
    for(i=0; i < g->num_vert; i++) {
        cur = g->array[i].head;
        while(cur!=NULL) {
            printf("Coming here inside while\n");
            printf("%d->%d\t", i, cur->dst);
            cur=cur->next;
        }
        printf("\n");
    }
}

struct graph *
create_graph(int v)
{
    int i = 0;
    struct graph *graph = malloc(sizeof (struct graph));
    graph->num_vert = v;
    graph->array = malloc(sizeof(struct adj_list) * v);

    for(i=0; i<v; i++) {
        graph->array[i].head = NULL;
    }
    return(graph);
}

void
add_edge(struct graph *g, int src, int dst)
{
    struct node *source_v = malloc(sizeof (struct node));
    struct node *dest_v = malloc(sizeof (struct node));
    
    dest_v->dst = dst;
    dest_v->next=NULL;

    source_v->dst = src;
    source_v->next=NULL;

    dest_v->next = g->array[src].head;
    g->array[src].head = dest_v;
    
    source_v->next = g->array[dst].head;
    g->array[dst].head = source_v;
}

int main(int argc, char **argv)
{
    int v = 0;
    printf("Enter how many vertices\n");
    scanf("%d", &v);
    struct graph *graph = create_graph(v);

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 3);

    print_graph(graph);
    //delete_edge();
}
