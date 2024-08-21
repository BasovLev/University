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

pNode search(pNode p, int key);
pNode findMin(pNode p);
void deleteNode(pNode *root, int key, pNode parent);
pNode delABNodes(pNode p, int a, int b);

void breadth_first( pNode p);
void delTree(pNode p);
void addABValues(pNode p, int n, int a, int b);

int main()
{
    pNode root;
    pNode p, t, tp, S;
    char in[100];
    int num, k;
    root = NULL;
    fgets(in, sizeof(in), stdin);
    char *tok = strtok(in, " ");
    while (tok != NULL) {
        if (sscanf(tok, "%d", &num) == 1) {
            insert(&root, num);
        }
        tok = strtok(NULL, " ");
    }
    scanf("%d", &k);
    getchar();  
    postOrder(root);
    printf("\n");
    S = search(root, k);
     if (S != NULL) {
        deleteNode(&root, k, NULL);
    } else {
        printf("!\n");
    }
    postOrder(root);
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

pNode search(pNode p, int key) {
    if (p == NULL || p->key == key) {
        return p;
    }
    
    if (key < p->key) {
        return search(p->left, key);
    } else {
        return search(p->right, key);
    }
}


pNode findMinParent(pNode root) {
    pNode parent = NULL;
    while (root->left) {
        parent = root;
        root = root->left;
    }
    return parent;
}

void deleteNode(pNode *root, int key, pNode parent) {
    if (!(*root)) return;
    
    if (key < (*root)->key)
        deleteNode(&((*root)->left), key, *root);
    else if (key > (*root)->key)
        deleteNode(&((*root)->right), key, *root);
    else {
        if (!(*root)->left && !(*root)->right) {
            if (parent) {
                if (parent->left) {
                    if (parent->left->key == (*root)->key) {
                        parent->left = NULL;
                    }
                }
                if (parent->right) {
                    if (parent->right->key == (*root)->key) {
                        parent->right = NULL;
                    }
                }
            }
            free(*root);
            *root = NULL;
        } else if (!(*root)->left || !(*root)->right) {
            pNode nodeToRemove = NULL;
            if ((*root)->left) {
                nodeToRemove = (*root)->left;
            } else {
                nodeToRemove = (*root)->right;
            }
            (*root)->left = nodeToRemove->left;
            (*root)->right = nodeToRemove->right;
            (*root)->key = nodeToRemove->key;
            free(nodeToRemove);
        } else {
            if (!(*root)->right->left) {
                (*root)->key = (*root)->right->key;
                pNode rightRightChild = (*root)->right->right;
                free((*root)->right);
                (*root)->right = rightRightChild;
            } else {
                pNode minNodeParent = findMinParent((*root)->right);
                (*root)->key = minNodeParent->left->key;
                free(minNodeParent->left);
                minNodeParent->left = NULL;
            }
        }
    }
}


pNode delABNodes(pNode p, int a, int b) {
    if (p == NULL) {
        return NULL;
    }
	
    p->left = delABNodes(p->left, a, b);
    p->right = delABNodes(p->right, a, b);

    if (p->key >= a && p->key <= b) {
        deleteNode(&p, p->key, NULL);
    }
    return p;
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


