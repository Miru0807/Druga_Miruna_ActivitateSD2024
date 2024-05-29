#include <stdio.h>
#include <stdlib.h>

#define DIMENSIUNE_MAXIMA 100

typedef struct {
    int varf;
    int elemente[DIMENSIUNE_MAXIMA];
} StivaVector;

void initializareStivaVector(StivaVector* s) {
    s->varf = -1;
}

int esteGoalaStivaVector(StivaVector* s) {
    return s->varf == -1;
}

int estePlinaStivaVector(StivaVector* s) {
    return s->varf == DIMENSIUNE_MAXIMA - 1;
}

void adaugaStivaVector(StivaVector* s, int x) {
    if (estePlinaStivaVector(s)) {
        printf("Stiva este plina.\n");
        return;
    }
    s->elemente[++(s->varf)] = x;
}

int extrageStivaVector(StivaVector* s) {
    if (esteGoalaStivaVector(s)) {
        printf("Stiva este goala.\n");
        return -1;
    }
    return s->elemente[(s->varf)--];
}

int varfulStivaVector(StivaVector* s) {
    if (esteGoalaStivaVector(s)) {
        printf("Stiva este goala.\n");
        return -1;
    }
    return s->elemente[s->varf];
}

int main() {
    StivaVector stiva;
    initializareStivaVector(&stiva);

    adaugaStivaVector(&stiva, 1);
    adaugaStivaVector(&stiva, 2);
    adaugaStivaVector(&stiva, 3);

    printf("Elementul de la varf: %d\n", varfulStivaVector(&stiva));

    printf("Elementele extrase din stiva: ");
    while (!esteGoalaStivaVector(&stiva)) {
        printf("%d ", extrageStivaVector(&stiva));
    }
    printf("\n");

    return 0;
}
