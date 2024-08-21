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
    } else {
        printf("Список пуст\n");
    }
}

void displayForward(List* list) {
    Elem* c = list->BegL;
    printf("Элементы списка в прямом порядке:\n");
    while (c != NULL) {
        printf("%4d", c->inf);
        c = c->next;
    }
}

void displayBackward(List* list) {
    Elem* c = list->EndL;
    printf("Элементы списка в обратном порядке:\n");
    while (c != NULL) {
        printf("%4d", c->inf);
        c = c->prev;
    }
}

int calculateSum(List* list) {
    int sum = 0;
    Elem* c = list->BegL;
    while (c != NULL) {
        sum += c->inf;
        c = c->next;
    }
    return sum;
}

Elem* findElement(List* list, int value) {
    Elem* pk = list->BegL;
    while (pk != NULL) {
        if (pk->inf == value) {
            return pk;
        }
        pk = pk->next;
    }
    return NULL;
}

void addMultipleAfter(List* list, Elem* target) {
    char in[100];
    int new;

    printf("Введите целые числа через пробел для добавления после найденного элемента (нажмите Enter для завершения):\n");
    fgets(in, sizeof(in), stdin);
    getchar();
    char *tok = strtok(in, " ");
    while (tok != NULL) {
        if (sscanf(tok, "%d", &new) == 1) {
            Elem* p = (Elem*)malloc(sizeof(Elem));
            p->inf = new;
            p->prev = target;
            p->next = target->next;

            target->next = p;

            if (p->next != NULL) {
                p->next->prev = p;
            } else {
                list->EndL = p;
            }
        }
        tok = strtok(NULL, " ");
    }

    printf("Элементы добавлены.\n");
}


void removeElement(List* list, Elem* target) {
    if (target != NULL) {
        if (target->prev != NULL) {
            target->prev->next = target->next;
        } else {
            list->BegL = target->next;
        }

        if (target->next != NULL) {
            target->next->prev = target->prev;
        } else {
            list->EndL = target->prev;
        }

        free(target);
    } else {
        printf("Элемент не найден\n");
    }
}

int main() {
    List* list = createList();
    char in[100];
    int num;

    printf("Введите целые числа через пробел для добавления в конец списка (нажмите Enter для завершения):\n");
    fgets(in, sizeof(in), stdin);

    char *tok = strtok(in, " ");
    while (tok != NULL) {
        if (sscanf(tok, "%d", &num) == 1) {
            addToEnd(list, num);
        }
        tok = strtok(NULL, " ");
    }
    
    // Найти в списке заданное пользователем значение
    int searchValue;
    printf("Введите значение для поиска: ");
    scanf("%d", &searchValue);

    Elem* pk = findElement(list, searchValue);

    if (pk != NULL) {
        // Если значение найдено, добавить несколько новых элементов после найденного элемента
        addMultipleAfter(list, pk);

        // Удалить найденный элемент и вывести все элементы списка на экран
        removeElement(list, pk);
        displayForward(list);
    } else {
        // Если значение отсутствует в списке, вывести все элементы исходного списка на экран
        printf("Значение не найдено в списке.\n");
        displayForward(list);
    }

    return 0;
}
