#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Muzeu {
    char* nume;
    float pretBilet;
    int nr_vizitatori;
};

struct Muzeu citireMuzeu() {
    struct Muzeu muzeu;  // Aici trebuie sa folosim tipul struct Muzeu, nu un pointer

    // nume
    char buffer[20];
    printf("Nume muzeu: ");
    scanf("%19s", buffer);  // Folosim %19s pentru a preveni overflow-ul buffer-ului
    muzeu.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(muzeu.nume, buffer);  // Folosim strcpy pentru ca nu mai avem restric?ii de securitate (de?i e bine s? folosim variantele mai sigure)

    // pret
    printf("Pret bilet intrare: ");
    scanf("%f", &muzeu.pretBilet);

    // nr_vizitatori
    printf("Numar vizitatori: ");
    scanf("%d", &muzeu.nr_vizitatori);

    return muzeu;  // Returnam structura, nu un pointer la structura
}

void citireMuzeuPrinParametru(struct Muzeu* pMuzeu) {
    char buffer[20];
    printf("Nume muzeu: ");
    scanf("%19s", buffer);  // Prevenirea overflow-ului

    pMuzeu->nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(pMuzeu->nume, buffer);

    printf("Pret bilet intrare: ");
    scanf("%f", &pMuzeu->pretBilet);

    printf("Numar vizitatori: ");
    scanf("%d", &pMuzeu->nr_vizitatori);
}

void afisareMuzeu(struct Muzeu muzeu) {
    printf("Muzeul %s are %d vizitatori, iar biletul costa %5.2f lei\n", muzeu.nume, muzeu.nr_vizitatori, muzeu.pretBilet);
}

int main() {  // În C, 'main' trebuie sa returneze un int
    struct Muzeu* pVectorMuzee = NULL;
    int numarMuzee;
    printf("Numar muzee: ");
    scanf("%d", &numarMuzee);
    pVectorMuzee = (struct Muzeu*)malloc(sizeof(struct Muzeu) * numarMuzee);

    for (int i = 0; i < numarMuzee; i++) {
        pVectorMuzee[i] = citireMuzeu();
    }

    for (int i = 0; i < numarMuzee; i++) {
        afisareMuzeu(pVectorMuzee[i]);
    }

    for (int i = 0; i < numarMuzee; i++) {
        free(pVectorMuzee[i].nume);
    }
    free(pVectorMuzee);

    return 0;  // Returnam 0 pentru a indica finalizarea cu succes a programului
}
