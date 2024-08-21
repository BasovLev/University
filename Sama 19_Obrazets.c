#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для представления элемента списка
typedef struct Node {
    int inf;
    struct Node *link;
} Node;

// Структура для представления списка
typedef struct List {
    Node *head;
} List;

// Функция для создания пустого списка
List* createList() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

// Функция для добавления элемента в начало списка
void addToStart(List *list, int inf) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->inf = inf;
    newNode->link = list->head;
    list->head = newNode;
}

// Функция для добавления элемента в конец списка
void addToEnd(List *list, int inf) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->inf = inf;
    newNode->link = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = newNode;
    }
}

// Функция для удаления элемента из начала списка
void removeFromStart(List *list) {
    if (list->head != NULL) {
        Node *temp = list->head;
        list->head = temp->link;
        free(temp);
    } else {
        printf("Список пуст\n");
    }
}

// Функция для удаления элемента из конца списка
void removeFromEnd(List *list) {
    if (list->head != NULL) {
        if (list->head->link == NULL) {
            free(list->head);
            list->head = NULL;
        } else {
            Node *current = list->head;
            while (current->link->link != NULL) {
                current = current->link;
            }
            free(current->link);
            current->link = NULL;
        }
    } else {
        printf("Список пуст\n");
    }
}

// Функция для вывода всех элементов списка на экран
void display(List *list) {
    Node *current = list->head;
    printf("Элементы списка:\n");
    while (current != NULL) {
        printf("%4d", current->inf);
        current = current->link;
    }
}

// Функция для поиска элемента с заданным значением в списке
Node* search(List *list, int value) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->inf == value) {
            return current;
        }
        current = current->link;
    }
    return NULL;
}

// Функция для добавления нового элемента перед заданным элементом
void addBefore(List *list, Node *targetNode, int inf) {
    if (targetNode != NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->inf = inf;
        newNode->link = targetNode;

        // Если targetNode - это головной элемент, то новый элемент становится новой головой списка
        if (targetNode == list->head) {
            list->head = newNode;
        } else {
            // Иначе, найдем предыдущий элемент перед targetNode и обновим его указатель
            Node *current = list->head;
            while (current->link != targetNode) {
                current = current->link;
            }
            current->link = newNode;
        }
    } else {
        printf("Элемент не найден\n");
    }
}

int main() {
    List *list = createList();
    char in[100]; // Предполагается, что строка не превышает 100 символов
    int num;
    int input;
    printf("Введите целые числа через пробел для добавления в стек: ");
    fgets(in, sizeof(in), stdin);

    char *token = strtok(in, " ");
    while (token != NULL) {
        if (sscanf(token, "%d", &num) == 1) {
            addToStart(list, num);
        }
        token = strtok(NULL, " ");
    }
    printf("Введите значение для поиска в списке: ");
    scanf("%d", &input);

    Node *foundNode = search(list, input);
    if (foundNode != NULL) {
        printf("Значение найдено в списке.\n");

        int newValue;
        printf("Введите новое значение для добавления перед найденным элементом: ");
        scanf("%d", &newValue);

        addBefore(list, foundNode, newValue);
    } else {
        printf("Значение не найдено в списке.\n");
    }

    // Вывести все элементы списка на экран
    display(list);

    return 0;
}
