#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stddef.h>
#include<iostream>



typedef struct {
    int id;
    char* titlu;
    int nrMateriale;
    float* preturi;
} Catalog;

Catalog citesteCatalog() {
    Catalog c;
    printf("Introduceti ID-ul catalogului: ");
    scanf_s("%d", &c.id);

    printf("Introduceti titlul catalogului: ");
    char buffer[256];
    scanf_s("%s", buffer);
    c.titlu = (char*)malloc(strlen(buffer) + 1);
    strcpy(c.titlu, buffer);

    printf("Introduceti numarul de materiale din catalog: ");
    scanf_s("%d", &c.nrMateriale);

    c.preturi = (float*)malloc(c.nrMateriale * sizeof(float));
    for (int i = 0; i < c.nrMateriale; i++) {
        printf("Introduceti pretul materialului %d: ", i + 1);
        scanf_s("%f", &c.preturi[i]);
    }

    return c;
}
float pretMediu(Catalog c) {
    float suma = 0;
    for (int i = 0; i < c.nrMateriale; i++) {
        suma += c.preturi[i];
    }
    return suma / c.nrMateriale;
}
void modificaTitlu(Catalog* c, char* noulTitlu) {
    free(c->titlu);
    c->titlu = (char*)malloc(strlen(noulTitlu) + 1);
    strcpy(c->titlu, noulTitlu);
}

void afiseazaCatalog(Catalog c) {
    printf("ID Catalog: %d\n", c.id);
    printf("Titlu: %s\n", c.titlu);
    printf("Numar materiale: %d\n", c.nrMateriale);
    printf("Preturi materiale:\n");
    for (int i = 0; i < c.nrMateriale; i++) {
        printf("Material %d: %.2f\n", i + 1, c.preturi[i]);
    }
}
