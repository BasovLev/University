#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m = 13; /*длина хэш-таблицы -- параметр*/
int l = 20; /*максимальная длина имён*/
int n = 10; /*число вводимых имён*/

typedef struct Elem{
    char *name;
    struct Elem *link;
} Elem;

int hash_func(char *m);
Elem **create_hash_tab(int len);
void finput(Elem **mas, int, FILE *);
void input(Elem **mas, int);
int find(Elem **ht, char *, int *pnc);
int max_len(Elem **ht);
double filling_coef(Elem **ht);
void delete_hash_tab(Elem ***pht);
void output(Elem **ht);

int main(void){
    Elem **ht;
    char line[l];
    int nc;
    /*FILE *fp;
    fp = fopen("\Users\basov\Documents\Учебные материалы для Вуза\Информатика\3 Семестр\Laba_22.txt", "r");*/
    ht = create_hash_tab(m);
    /*finput(ht, 10, fp);*/
    input(ht, n);
    scanf("%s", line);
    if (find(ht, line, &nc)){
        printf("not found\n");
    }
    else{
        printf("%s\n", line);
    }
    printf("%d\n", max_len(ht));
    printf("%lf\n", filling_coef(ht));
    delete_hash_tab(&ht);
    return 0;
}
int hash_func(char *str){
    int hash = 0, i = 0, C = 678;
    while (str[i] != '\0'){
        hash = (hash*C + (str[i] - '0'))%m;
        i++;
    }
    return hash;
}
Elem **create_hash_tab(int len){
    Elem **p;
    int i;
    p = (Elem **)malloc(len*sizeof(Elem *));
    for (i = 0; i < len; i++){
        p[i] = NULL;
    }
    return p;
}
void finput(Elem **ht, int number, FILE *fp){
    char *line;
    Elem *p, *pt;
    int i, hash;
    for (i = 0; i < number; i++){
        line = (char *)malloc(l*sizeof(char));
        fscanf(fp, "%s", line);
        line[l - 1] = '\0';
        hash = hash_func(line);
        p = (Elem *) malloc(sizeof(Elem));
        p -> name = line;
        p -> link = NULL;
        if (ht[hash] == NULL){
            ht[hash] = p;
        }
        else{
            pt = ht[hash];
            while (pt -> link){
                pt = pt -> link;
            }
            pt -> link = p;
        }
    }
    return;
}
void input(Elem **ht, int number){
    char *line;
    Elem *p, *pt;
    int i, hash;
    for (i = 0; i < number; i++){
        line = (char *)malloc(l*sizeof(char));
        scanf("%s", line);
        line[l - 1] = '\0';
        hash = hash_func(line);
        p = (Elem *) malloc(sizeof(Elem));
        p -> name = line;
        p -> link = NULL;
        if (ht[hash] == NULL){
            ht[hash] = p;
        }
        else{
            pt = ht[hash];
            while (pt -> link){
                pt = pt -> link;
            }
            pt -> link = p;
        }
    }
    return;
}
int find(Elem **ht, char *line, int *pnc){
    int hash;
    Elem *p;
    hash = hash_func(line);
    p = ht[hash];
    *pnc = 0;
    while (p){
        (*pnc)++;
        if (!strcmp(p -> name, line)){
            return 0;
        }
        p = p -> link;
    }
    return 1;
}
int max_len(Elem **ht){
    int max = 0, i, len;
    Elem *p;
    for (i = 0; i < m; i++){
        len = 0;
        p = ht[i];
        while (p){
            len++;
            p = p -> link;
        }
        max = (max > len)? max: len;
    }
    return max;
}
double filling_coef(Elem **ht){
    int num = 0, i;
    Elem *p;
    for (i = 0; i < m; i++){
        p = ht[i];
        while (p){
            num++;
            p = p -> link;
        }
    }
    return (double) num / m;
}
void delete_hash_tab(Elem ***pht){
    Elem *p, *pt;
    int i;
    for (i = 0; i < m; i++){
        p = (*pht)[i];
        while (p){
            pt = p;
            p = p -> link;
            free(pt);
        }
    }
    free(*pht);
    *pht = NULL;
}
void output(Elem **ht){
    Elem *p;
    int i;
    for (i = 0; i < m; i ++){
        p = ht[i];
        printf("hash code: %2d\n",i);
        if (!p){
            printf("NULL\n");
        }
        while(p){
            printf("%s\n", p -> name);
            p = p -> link;
        }
        
    }
    return;
}
