#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem {
    int inf;
    struct Elem* next;
    struct Elem* prev;
} Elem;

typedef struct List {
    Elem* BegL;
    Elem* EndL;
} List;

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    list->BegL = NULL;
    list->EndL = NULL;
    return list;
}

void addToStart(List* list, int inf) {
    Elem* p = (Elem*)malloc(sizeof(Elem));
    p->inf = inf;
    p->next = list->BegL;
    p->prev = NULL;

    if (list->BegL != NULL) {
        list->BegL->prev = p;
    } else {
        list->EndL = p;
    }

    list->BegL = p;
}

void addToEnd(List* list, int inf) {
    Elem* p = (Elem*)malloc(sizeof(Elem));
    p->inf = inf;
    p->next = NULL;
    p->prev = list->EndL;

    if (list->EndL != NULL) {
        list->EndL->next = p;
    } else {
        list->BegL = p;
    }

    list->EndL = p;
}

void removeFromStart(List* list) {
    if (list->BegL != NULL) {
        Elem* t = list->BegL;
        list->BegL = t->next;

        if (list->BegL != NULL) {
            list->BegL->prev = NULL;
        } else {
            list->EndL = NULL;
        }

        free(t);
    }
}

void removeFromEnd(List* list) {
    if (list->EndL != NULL) {
        Elem* t = list->EndL;
        list->EndL = t->prev;

        if (list->EndL != NULL) {
            list->EndL->next = NULL;
        } else {
            list->BegL = NULL;
        }

        free(t);
    }
}

void displayForward(List* list) {
    Elem* c = list->BegL;
    while (c != NULL) {
        printf("%4d", c->inf);
        c = c->next;
    }
}

void displayBackward(List* list) {
    Elem* c = list->EndL;
    while (c != NULL) {
        printf("%4d", c->inf);
        c = c->prev;
    }
}

int FullSum(List* list) {
    int sum = 0;
    Elem* c = list->BegL;
    while (c != NULL) {
        sum += c->inf;
        c = c->next;
    }
    return sum;
}

int main() {
    List* list = createList();
    char in[100];
    int num;
    fgets(in, sizeof(in), stdin);
    char *tok = strtok(in, " ");
    while (tok != NULL) {
        if (sscanf(tok, "%d", &num) == 1) {
            addToStart(list, num);
        }
        tok = strtok(NULL, " ");
    }

    removeFromEnd(list);
    removeFromEnd(list);
    displayBackward(list);
    int sum = FullSum(list);
    printf("\n%d\n", sum);

    return 0;
}
