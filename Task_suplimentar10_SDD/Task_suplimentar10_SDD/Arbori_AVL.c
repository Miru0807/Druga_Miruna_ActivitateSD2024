#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

// ARBORE AVL FACTURA

typedef struct Factura {
    int nr;
    char* data;
    char* nume;
    float val;
    int nr_prod;
} Factura;

typedef struct Node {
    struct Node* left;
    struct Node* right;
    Factura* info;
    int balanceFactor;
} Node;

Factura* createElement(int nr, const char* data, const char* nume, float val, int nr_prod) {
    Factura* fact = (Factura*)malloc(sizeof(Factura));
    fact->nr = nr;
    fact->data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(fact->data, data);
    fact->nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(fact->nume, nume);
    fact->val = val;
    fact->nr_prod = nr_prod;
    return fact;
}

Node* createNode(Factura* f) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->left = newNode->right = NULL;
    newNode->info = f;
    newNode->balanceFactor = 0;
    return newNode;
}

static int maxF(int a, int b)
{
    return a > b ? a : b;
}

int getHeight(Node* root)
{
    if (root == NULL)
        return 0;
    else
        return 1 + maxF(getHeight(root->left), getHeight(root->right));
}

int getBalanceFact(Node* root) {
    if (root == NULL)
        return 0;
    else
        return getHeight(root->left) - getHeight(root->right);
}

void rotateLeft(Node* root)
{
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root = temp;
}

void rotateRight(Node* root)
{
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root = temp;
}

Node* rebalance(Node* root)
{
    root->balanceFactor = getBalanceFact(root);
    if (root->balanceFactor == 2)
    {
        if (getBalanceFact(root->left) != 1)
            rotateLeft(root->left);
        rotateRight(root);
    }
    else
        if (root->balanceFactor == -2)
        {
            if (getBalanceFact(root->right) != -1)
                rotateRight(root->right);
            rotateLeft(root);
        }
    return root;
}

void insert(Node** root, Factura* f) {

    if (*root == NULL)
        *root = createNode(f);
    else
    {
        if (f->nr < (*root)->info->nr)
            insert(&(*root)->left, f);
        else
            if (f->nr > (*root)->info->nr)
                insert(&(*root)->right, f);
            else
                printf("Duplicate key. The value cannot be inserted");
    }
    *root = rebalance(*root);
}

void printFactura(Node* root)
{
    printf("\n%d, %s, %s, %f, %d", root->info->nr, root->info->data, root->info->nume, root->info->val, root->info->nr_prod);
}

void inOrder(Node* root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printFactura(root);
        inOrder(root->right);
    }
}

void printNoFact(Node* root)
{
    printf("\n%d", root->info->nr);
}

void printLvl(Node* root, int lvl)
{
    if (root != NULL)
    {
        for (int i = 0; i < lvl; i++)
            printf("\t");
        printNoFact(root);
        printLvl(root->left, lvl + 1);
        printLvl(root->right, lvl + 1);
    }
    else
    {
        for (int i = 0; i < lvl; i++)
            printf("\t");
        printf("NULL\n");
    }
}

float valTotala(Node* root, const char* data)
{
    if (root == NULL)
        return 0;
    else
        if (strcmp(root->info->data, data) > 0)
            return root->info->val + valTotala(root->left, data) + valTotala(root->right, data);
        else
            return valTotala(root->left, data) + valTotala(root->right, data);

}

int facturiEmise(Node* root, const char* client)
{
    if (root == NULL)
        return 0;
    else
        if (strcmp(root->info->nume, client) == 0)
            return 1 + facturiEmise(root->left, client) + facturiEmise(root->right, client);
        else
            return facturiEmise(root->left, client) + facturiEmise(root->right, client);
}

void correct(Node* root)
{
    if (root != NULL)
    {
        root->info->val += 2.5;
        correct(root->left);
        correct(root->right);
    }
}

void deleteLogical(Node* root, Node* leftTree)
{
    if (leftTree->right != NULL)
        deleteLogical(root, leftTree->right);
    else
    {
        Factura* temp = root->info;
        root->info = leftTree->info;
        free(temp->data);
        free(temp->nume);
        free(temp);
        Node* aux = leftTree;
        leftTree = aux->left;
        free(aux);
    }
}

void deleteNode(Node** root, int nr) {
    if (*root == NULL) {
        printf("The factura does not exist");
        return;
    }

    if (nr < (*root)->info->nr) {
        deleteNode(&((*root)->left), nr);
    }
    else if (nr > (*root)->info->nr) {
        deleteNode(&((*root)->right), nr);
    }
    else {
        if ((*root)->left == NULL) {
            Node* temp = (*root)->right;
            free((*root)->info->data);
            free((*root)->info->nume);
            free((*root)->info);
            free(*root);
            *root = temp;
        }
        else if ((*root)->right == NULL) {
            Node* temp = (*root)->left;
            free((*root)->info->data);
            free((*root)->info->nume);
            free((*root)->info);
            free(*root);
            *root = temp;
        }
        else {
            Node* temp = (*root)->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            (*root)->info = temp->info;
            deleteNode(&((*root)->right), temp->info->nr);
        }
    }

    if (*root != NULL) {
        (*root)->balanceFactor = getBalanceFact(*root);

        if ((*root)->balanceFactor > 1 && getBalanceFact((*root)->left) >= 0) {
            rotateRight(*root);
        }

        if ((*root)->balanceFactor > 1 && getBalanceFact((*root)->left) < 0) {
            rotateLeft((*root)->left);
            rotateRight(*root);
        }

        if ((*root)->balanceFactor < -1 && getBalanceFact((*root)->right) <= 0) {
            rotateLeft(*root);
        }

        if ((*root)->balanceFactor < -1 && getBalanceFact((*root)->right) > 0) {
            rotateRight((*root)->right);
            rotateLeft(*root);
        }
    }
}
int main()
{
    Factura* f1 = createElement(23, "2019.01.20", "Alex", 222, 9);
    Factura* f2 = createElement(20, "2019.04.22", "Bob", 45, 3);
    Factura* f3 = createElement(30, "2019.03.05", "Alice", 23, 1);
    Factura* f4 = createElement(17, "2019.03.13", "Adi", 40, 2);
    Factura* f5 = createElement(21, "2019.02.24", "Ana", 55, 4);
    Factura* f6 = createElement(28, "2019.05.17", "Vader", 1, 40);
    Factura* f7 = createElement(35, "2019.06.02", "Alex", 22, 5);

    Node* root = NULL;

    insert(&root, f1);
    insert(&root, f2);
    insert(&root, f3);
    insert(&root, f4);
    insert(&root, f5);
    insert(&root, f6);
    insert(&root, f7);

    inOrder(root);
    printf("\n-------------LEVEL PRINT-------------\n");
    printLvl(root, 0);
    printf("\n-------------TOTAL PRINT-------------\n");
    printf("\n%f", valTotala(root, "2018.07.17"));
    printf("\n-------------FACTURI EMISE-------------\n");
    printf("\n%d", facturiEmise(root, "Adi"));
    printf("\n-------------CORECTATE-------------\n");
    correct(root);
    inOrder(root);
    deleteNode(root, 23);
    printf("\n-------------DUPA STERGERE-------------\n");
    inOrder(root);
    printf("\n-------------LEVEL PRINT-------------\n");
    printLvl(root, 0);

    return 0;
}