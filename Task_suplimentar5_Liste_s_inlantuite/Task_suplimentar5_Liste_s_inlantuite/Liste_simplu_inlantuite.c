#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


typedef struct {
    int cod;
    char* denumire;
    float cantitate;
    float pret;
}produs;

typedef struct {
    struct nodLs* next;
    produs info;

}nodLs;

nodLs* inserare(nodLs* cap, produs p) {

    nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
    nou->info.cod = p.cod;
    nou->info.cantitate = p.cantitate;
    nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
    strcpy(nou->info.denumire, p.denumire);

    nou->info.pret = p.pret;
    nou->next = NULL;

    if (cap == NULL) {
        cap = nou;
    }
    else
    {
        nodLs* aux = cap;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nou;

    }
    return cap;
}
void traversare(nodLs* cap) {

    nodLs* aux = cap;
    while (aux != NULL)
    {
        printf("Id-ul:%d , Denumirea:%s , cantitatea:%5.2f, Pretul:%5.2f", aux->info.cod, aux->info.denumire, aux->info.cantitate, aux->info.pret);
        printf("\n");
        aux = aux->next;
    }

}
void dezalocare(nodLs* cap) {

    nodLs* aux = cap;
    while (aux != NULL) {
        nodLs* urmator = aux->next;
        free(aux->info.denumire);
        free(aux);
        aux = urmator;
    }

}
void main()
{
    FILE* f = fopen("fisier.txt", "r");
    int n;
    produs p;
    nodLs* cap = NULL;
    char buffer[20];
    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &p.cod);
        fscanf(f, "%s", buffer);
        p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(p.denumire, buffer);
        fscanf(f, "%f", &p.cantitate);
        fscanf(f, "%f", &p.pret);

        cap = inserare(cap, p);
        free(p.denumire);

    }
    fclose(f);

    traversare(cap);
    dezalocare(cap);
    // printf("Miruna");

}

