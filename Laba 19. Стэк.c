#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem {
    int inf;
    struct Elem *link;
} Elem;

typedef struct Stack {
    Elem *top;
} Stack;

Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, int inf);
int del(Stack *stack);
void display(Stack *stack);
int countElements(Stack *stack);

int main() {
    Stack *stack = createStack();
    char input[100]; 
    int num;
    fgets(input, sizeof(input), stdin);
    char *ch = strtok(input, " ");
    while (ch != NULL) {
        if (sscanf(ch, "%d", &num) == 1) {
            push(stack, num);
        }
        ch = strtok(NULL, " ");
    }

    del(stack);
    del(stack);
    display(stack);
    printf("\n%d\n", countElements(stack));

    return 0;
}

void push(Stack *stack, int inf) {
    Elem *p = (Elem*)malloc(sizeof(Elem));
    p->inf = inf;
    p->link = stack->top;
    stack->top = p;
}

int del(Stack *stack) {
    if (stack->top == NULL) {
        printf("Стек пуст(\n");
        return -1;
    }
    Elem *t = stack->top;
    int inf = t->inf;
    stack->top = t->link;
    free(t);
    return inf;
}

void display(Stack *stack) {
    Elem *c = stack->top;
    while (c != NULL) {
        printf("%4d", c->inf);
        c = c->link;
    }
}

int countElements(Stack *stack) {
    int count = 0;
    Elem *c = stack->top;
    while (c != NULL) {
        count++;
        c = c->link;
    }
    return count;
}