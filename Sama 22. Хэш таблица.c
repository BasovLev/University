#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m = 13; 
int l = 20; 
int n = 10; 

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
void add(Elem **, char *);
void remove_el(Elem **ht, char *line);

int main(void){
    Elem **ht;
    char *line;

    ht = create_hash_tab(m);
    input(ht, n);
    
    line = (char *)malloc(l*sizeof(char));
    scanf("%s", line);
    add(ht, line);
    
    line = (char *)malloc(l*sizeof(char));
    scanf("%s", line);
    add(ht, line);
    
    line = (char *)malloc(l * sizeof(char));
    scanf("%s", line);
    remove_el(ht, line);
    
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

void add(Elem **ht, char *line){
    int hash;
    Elem *p, *pt;
    hash = hash_func(line);
    p = (Elem *) malloc(sizeof(Elem));
    p -> link = NULL;
    p -> name = line;
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
    return;
}

void remove_el(Elem **ht, char *line) {
    int hash = hash_func(line);
    Elem *c = ht[hash];
    Elem *prev = NULL;
	
    while (c != NULL && strcmp(c->name, line) != 0) {
        prev = c;
        c = c->link;
    }

    if (c != NULL) {
        if (prev == NULL) {
            ht[hash] = c->link;
        } else {
            prev->link = c->link;
        }

        free(c->name);
        free(c);
    }
}