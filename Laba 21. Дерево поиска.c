#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;
typedef Node *pNode;

void preOrder(pNode p);
void postOrder(pNode p);
void inOrder(pNode p);
void insert(pNode *p, int val);
int sumOneChild(pNode p);
int TreeLevels(pNode p);

void breadth_first( pNode p);
void delTree(pNode p);
void addABValues(pNode p, int n, int a, int b);

int main()
{
    pNode root;
    pNode p, t, tp;
    char in[100];
    int num;
    root = NULL;
    fgets(in, sizeof(in), stdin);
    char *tok = strtok(in, " ");
    while (tok != NULL) {
        if (sscanf(tok, "%d", &num) == 1) {
            insert(&root, num);
        }
        tok = strtok(NULL, " ");
    }
    postOrder(root);
    sumOneChild(root);
    printf("\n%d", sumOneChild(root));
    return 0;
}

void preOrder(pNode p) {
    if (p != NULL) {
        printf("%3d ", p->key);
        preOrder(p->left);
        preOrder(p->right);
    }
}

void postOrder(pNode p) {
    if (p != NULL) {
        postOrder(p->left);
        postOrder(p->right);
        printf("%3d", p->key);
    }
}

void inOrder(pNode p) {
    if (p != NULL) {
        inOrder(p->left);
        printf("%3d", p->key);
        inOrder(p->right);
    }
}
int sumOneChild(pNode p) {
    if (p == NULL) {
        return 0;
    }
    int leftSum;
    int rightSum;
    int sum;
    
    leftSum = sumOneChild(p->left);
    rightSum = sumOneChild(p->right);
    
    if ((p->left == NULL && p->right != NULL) || (p->left != NULL && p->right == NULL)) {
        return  p->key + leftSum + rightSum;
    }
    sum = leftSum + rightSum;
    return sum;
}


int TreeLevels(pNode p) {
    if (p == NULL) {
        return 0;
    }
    int leftLevels;
    int rightLevels;
    
    leftLevels = TreeLevels(p->left);
    rightLevels = TreeLevels(p->right);
    return (leftLevels > rightLevels ? leftLevels : rightLevels);
}

void insert(pNode *p, int val) {
    if (*p == NULL) {
        *p = (Node *) malloc(sizeof(Node));
        (*p)->key = val;
        (*p)->left = NULL;
        (*p)->right = NULL;
    } else {
        if (val < (*p)->key)
            insert(&( (*p)->left ), val);
        else
            insert(&( (*p)->right ), val);
    }
}

// Дополнительные функции

 /*void breadth_first( pNode p) {
    if (p == 0) {
        return;
    } else {
         Не получается, почему-то(
        if (c <= d) {
            printf("%d ", p->key);
            c += 1;
            breadth_first(p->left);
        } else if (c> d) {
            d += 1;
            printf("%d ", p->key);
            breadth_first(p->right);
        }
    }
} */
void addABValues(pNode p, int n, int a, int b) {
    for (int i = 0; i < n; ++i) {
        int randVal = a + rand() % (b - a + 1);
        
        insert(&p, randVal);
    }
}
            
void delTree(pNode p) {
    if (p != NULL) {
        delTree(p->left);
        delTree(p->right);
        free(p);
    }
}
















