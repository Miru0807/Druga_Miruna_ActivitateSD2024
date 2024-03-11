#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <string.h>
#include <stdio.h>

struct Film {
    char* nume;
    float pretBilet;
    int nr_vizitatori;
};

struct Film citireFilm() {
    struct Film film;
    char buffer[20];
    printf("Nume film: ");
    scanf_s("%19s", buffer, sizeof(buffer));  // Corect?m ?i lungimea buffer-ului în scanf_s
    film.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy_s(film.nume, strlen(buffer) + 1, buffer);

    printf("Pret bilet intrare: ");
    scanf_s("%f", &film.pretBilet);

    printf("Numar vizitatori: ");
    scanf_s("%d", &film.nr_vizitatori);

    return film;
}

void afisareFilm(struct Film film) {  // Redenumim func?ia pentru a reflecta corect structura 'Film'
    printf("Filmul %s are %d vizitatori, iar biletul costa %5.2f lei\n", film.nume, film.nr_vizitatori, film.pretBilet);  // Corect?m numele variabilei de accesat
}

struct Film** citireMatrice(int* n, int* m) {
    printf("Numarul de linii este: ");
    scanf_s("%d", n);
    printf("Numarul de coloane: ");
    scanf_s("%d", m);

    struct Film** matrice = (struct Film**)malloc(sizeof(struct Film*) * (*n));

    for (int i = 0; i < *n; i++) {
        matrice[i] = (struct Film*)malloc(sizeof(struct Film) * (*m));
        for (int j = 0; j < *m; j++) {
            matrice[i][j] = citireFilm();
        }
    }

    return matrice;
}

int main() {
    int nrLinii = 0, nrColoane = 0;
    struct Film** matrice = citireMatrice(&nrLinii, &nrColoane);

    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < nrColoane; j++) {
            afisareFilm(matrice[i][j]);
        }
        printf("\n");
    }

    // Dezalocarea memoriei
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < nrColoane; j++) {
            free(matrice[i][j].nume);
        }
        free(matrice[i]);
    }
    free(matrice);

    return 0;
}
