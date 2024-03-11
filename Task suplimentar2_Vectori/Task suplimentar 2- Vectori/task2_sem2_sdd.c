#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<malloc.h>

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

int main() {
    int n = 5; // Numărul de obiecte Catalog
    Catalog* cataloguri = (Catalog*)malloc(n * sizeof(Catalog));

    // Citirea catalogurilor
    for (int i = 0; i < n; i++) {
        printf("Catalogul %d:\n", i + 1);
        cataloguri[i] = citesteCatalog();
    }

    // Apelarea funcțiilor cerute (implementările vor fi definite mai jos)
    Catalog* cataloguriFiltrate = NULL;
    int nrFiltrate = filtreazaCataloguri(cataloguri, n, &cataloguriFiltrate, 100); // Condiție exemplu: nrPagini > 100

    Catalog* cataloguriMutate = NULL;
    int nrMutate = mutaCataloguri(cataloguri, n, &cataloguriMutate, 50); // Condiție exemplu: nrPagini < 50

    Catalog* cataloguriConcatenate = NULL;
    int nrConcatenate = concateneazaCataloguri(cataloguriFiltrate, nrFiltrate, cataloguriMutate, nrMutate, &cataloguriConcatenate);

    // Afișarea vectorilor
    printf("Cataloguri Filtrate:\n");
    afiseazaVector(cataloguriFiltrate, nrFiltrate);

    printf("Cataloguri Mutate:\n");
    afiseazaVector(cataloguriMutate, nrMutate);

    printf("Cataloguri Concatenate:\n");
    afiseazaVector(cataloguriConcatenate, nrConcatenate);

    // Eliberarea memoriei
    free(cataloguri);
    free(cataloguriFiltrate);
    free(cataloguriMutate);
    free(cataloguriConcatenate);

    return 0;
}

int filtreazaCataloguri(Catalog* sursa, int nrSursa, Catalog** destinatie, int prag) {
    int count = 0;
    for (int i = 0; i < nrSursa; i++) {
        if (sursa[i].nrMateriale > prag) { // Condiția de filtrare
            count++;
        }
    }

    *destinatie = (Catalog*)malloc(count * sizeof(Catalog));
    int j = 0;
    for (int i = 0; i < nrSursa; i++) {
        if (sursa[i].nrMateriale > prag) {
            (*destinatie)[j++] = sursa[i]; // Copierea catalogurilor care îndeplinesc condiția
        }
    }

    return count;
}

int mutaCataloguri(Catalog* sursa, int nrSursa, Catalog** destinatie, int prag) {
    int count = 0;
    for (int i = 0; i < nrSursa; i++) {
        if (sursa[i].nrMateriale < prag) { // Condiția de mutare
            count++;
        }
    }

    *destinatie = (Catalog*)malloc(count * sizeof(Catalog));
    int j = 0;
    for (int i = 0; i < nrSursa; i++) {
        if (sursa[i].nrMateriale < prag) {
            (*destinatie)[j++] = sursa[i];
            sursa[i].titlu = NULL; // Indicăm că obiectul a fost mutat
            sursa[i].preturi = NULL;
        }
    }

    return count;
}


int concateneazaCataloguri(Catalog* primul, int nrPrimul, Catalog* alDoilea, int nrAlDoilea, Catalog** rezultat) {
    int total = nrPrimul + nrAlDoilea;
    *rezultat = (Catalog*)malloc(total * sizeof(Catalog));

    for (int i = 0; i < nrPrimul; i++) {
        (*rezultat)[i] = primul[i]; // Copierea primului vector
    }

    for (int i = 0; i < nrAlDoilea; i++) {
        (*rezultat)[nrPrimul + i] = alDoilea[i]; // Copierea celui de-al doilea vector
    }

    return total;
}
void afiseazaVector(Catalog* vector, int n) {
    for (int i = 0; i < n; i++) {
        afiseazaCatalog(vector[i]);
    }
}
