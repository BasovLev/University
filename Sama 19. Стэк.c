#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elem {
    int inf;
    struct Elem *link;
} Elem;

typedef struct List {
    Elem *Top;
} List;

List* createList() {
    List *list = (List*)malloc(sizeof(List));
    list->Top = NULL;
    return list;
}

void addToStart(List *list, int inf) {
    Elem *newElem = (Elem*)malloc(sizeof(Elem));
    newElem->inf = inf;
    newElem->link = list->Top;
    list->Top = newElem;
}

void addToEnd(List *list, int inf) {
    Elem *newElem = (Elem*)malloc(sizeof(Elem));
    newElem->inf = inf;
    newElem->link = NULL;

    if (list->Top == NULL) {
        list->Top = newElem;
    } else {
        Elem *c = list->Top;
        while (c->link != NULL) {
            c = c->link;
        }
        c->link = newElem;
    }
}

void removeFromStart(List *list) {
    if (list->Top != NULL) {
        Elem *t = list->Top;
        list->Top = t->link;
        free(t);
    }
}

void removeFromEnd(List *list) {
    if (list->Top != NULL) {
        if (list->Top->link == NULL) {
            free(list->Top);
            list->Top = NULL;
        } else {
            Elem *c = list->Top;
            while (c->link->link != NULL) {
                c = c->link;
            }
            free(c->link);
            c->link = NULL;
        }
    }
}

void display(List *list) {
    Elem *c = list->Top;
    while (c != NULL) {
        printf("%4d", c->inf);
        c = c->link;
    }
}

Elem* search(List *list, int value) {
    Elem *c = list->Top;
    while (c != NULL) {
        if (c->inf == value) {
            return c;
        }
        c = c->link;
    }
    return NULL;
}

void addBefore(List *list, Elem *targetElem, int inf) {
    if (targetElem != NULL) {
        Elem *newElem = (Elem*)malloc(sizeof(Elem));
        newElem->inf = inf;
        newElem->link = targetElem;

        if (targetElem == list->Top) {
            list->Top = newElem;
        } else {
            Elem *c = list->Top;
            while (c->link != targetElem) {
                c = c->link;
            }
            c->link = newElem;
        }
    }
}

int main() {
    List *list = createList();
    char in[100]; 
    int num;
    int input;
    fgets(in, sizeof(in), stdin);

    char *tok = strtok(in, " ");
    while (tok != NULL) {
        if (sscanf(tok, "%d", &num) == 1) {
            addToStart(list, num);
        }
        tok = strtok(NULL, " ");
    }
    
    scanf("%d", &input);

    Elem *foundElem = search(list, input);
    if (foundElem != NULL) {

        int newValue;
        scanf("%d", &newValue);

        addBefore(list, foundElem, newValue);
    }

    display(list);
    return 0;
}
