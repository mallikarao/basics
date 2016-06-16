#include<stdio.h>
#include <stdlib.h>

#define YES 1
#define NO 0

struct stack {
    int capacity;
    int *array;
    int top;
};

int
isfull_stack(struct stack *s)
{
    if(s->top == s->capacity-1) {
        return YES;
    }
    return NO;
}

int
push(struct stack *s, int data)
{
    // check if full, if yes return, else, push the element.
    if(isfull_stack(s)) {
        printf("The stack is full\n");
        return -1;
    }
    printf("Pushing %d\n", data);
    s->array[++s->top] = data;
    return 0;
}

int
isempty_stack(struct stack *s)
{
    if(s->top == -1) {
        return YES;
    } else return NO;
}

int
pop(struct stack *s)
{
    // check if empty, if yes return, else pop the element in top
    if(isempty_stack(s)) {
        printf("Stack empty, nothing to pop\n");
        return -1;
    }
    printf("Popping %d\n", s->array[s->top]);
    return (s->array[s->top--]);
}

struct stack *
init_stack(struct stack *s, int capacity)
{
    s = malloc(sizeof(struct stack));
    s->capacity = capacity;
    s->top = -1;
    s->array = malloc(sizeof(int) * capacity);
    return s;
}

void
get_top(struct stack *s)
{
    printf("top element is: %d\n", s->array[s->top]);
}

void
print_stack(struct stack *s)
{
    int cur=s->top;
    while(cur>=0) {
        printf("%d\n", s->array[cur]);
        cur--;
    }
}

int main(int argc, char **argv)
{
    struct stack *s;
    s = init_stack(s, 4);
    push(s, 8);
    push(s, 9);
    print_stack(s); 
    get_top(s);
    
    pop(s);
    get_top(s);
    printf("isempty ? :%d\n", isempty_stack(s));
    printf("isfull ? :%d\n", isfull_stack(s));
    print_stack(s);
}
