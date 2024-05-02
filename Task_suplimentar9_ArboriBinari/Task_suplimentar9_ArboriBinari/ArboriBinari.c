#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Nod {
    int cheie;
    struct Nod* stanga;
    struct Nod* dreapta;
} Nod;

Nod* creareNod(int cheie) {
    Nod* nouNod = (Nod*)malloc(sizeof(Nod));
    nouNod->cheie = cheie;
    nouNod->stanga = NULL;
    nouNod->dreapta = NULL;
    return nouNod;
}

Nod* inserare(Nod* radacina, int cheie) {
    if (radacina == NULL) {
        return creareNod(cheie);
    }

    if (cheie < radacina->cheie) {
        radacina->stanga = inserare(radacina->stanga, cheie);
    }
    else if (cheie > radacina->cheie) {
        radacina->dreapta = inserare(radacina->dreapta, cheie);
    }

    return radacina;
}

int inaltime(Nod* nod) {
    if (nod == NULL) {
        return 0;
    }
    else {
        int inaltimeStanga = inaltime(nod->stanga);
        int inaltimeDreapta = inaltime(nod->dreapta);
        return (inaltimeStanga > inaltimeDreapta) ? (inaltimeStanga + 1) : (inaltimeDreapta + 1);
    }
}

Nod* stergereNod(Nod* radacina, int cheie) {
    if (radacina == NULL) {
        return radacina;
    }

    if (cheie < radacina->cheie) {
        radacina->stanga = stergereNod(radacina->stanga, cheie);
    }
    else if (cheie > radacina->cheie) {
        radacina->dreapta = stergereNod(radacina->dreapta, cheie);
    }
    else {
        if (radacina->stanga == NULL) {
            Nod* temp = radacina->dreapta;
            free(radacina);
            return temp;
        }
        else if (radacina->dreapta == NULL) {
            Nod* temp = radacina->stanga;
            free(radacina);
            return temp;
        }

        Nod* temp = radacina->dreapta;
        while (temp->stanga != NULL) {
            temp = temp->stanga;
        }
        radacina->cheie = temp->cheie;
        radacina->dreapta = stergereNod(radacina->dreapta, temp->cheie);
    }
    return radacina;
}

Nod* subarboreCuInaltimeMaiMare(Nod* radacina) {
    if (radacina == NULL) {
        return NULL;
    }

    int inaltimeStanga = inaltime(radacina->stanga);
    int inaltimeDreapta = inaltime(radacina->dreapta);

    if (inaltimeStanga > inaltimeDreapta) {
        printf("Subarborele stang are inaltimea mai mare\n");
        return radacina->stanga;
    }
    else {
        printf("Subarborele drept are inaltimea mai mare\n");
        return radacina->dreapta;
    }
}

int numaraNoduri(Nod* radacina) {
    if (radacina == NULL) {
        return 0;
    }
    else {
        return 1 + numaraNoduri(radacina->stanga) + numaraNoduri(radacina->dreapta);
    }
}

Nod* subArboreMaiMulteN(Nod* radacina) {
    if (radacina == NULL) {
        return NULL;
    }

    int numarNoduriStanga = numaraNoduri(radacina->stanga);
    int numarNoduriDreapta = numaraNoduri(radacina->dreapta);

    if (numarNoduriStanga > numarNoduriDreapta) {
        return radacina->stanga;
    }
    else {
        return radacina->dreapta;
    }
}

void parcurgereInOrdine(Nod* radacina) {
    if (radacina != NULL) {
        parcurgereInOrdine(radacina->stanga);
        printf("%d ", radacina->cheie);
        parcurgereInOrdine(radacina->dreapta);
    }
}

int main() {
    Nod* radacina = NULL;
    radacina = inserare(radacina, 50);
    inserare(radacina, 30);
    inserare(radacina, 20);
    inserare(radacina, 40);
    inserare(radacina, 70);
    inserare(radacina, 60);
    inserare(radacina, 80);

    printf("Parcurgere in ordine a arborelui de cautare binara: ");
    parcurgereInOrdine(radacina);
    printf("\n==================================\n");

    int cheieDeSters = 20;
    radacina = stergereNod(radacina, cheieDeSters);
    printf("Parcurgere in ordine dupa stergerea nodului cu cheia %d: ", cheieDeSters);
    parcurgereInOrdine(radacina);
    printf("\n==================================\n");

    Nod* subarbore = subarboreCuInaltimeMaiMare(radacina);
    if (subarbore != NULL) {
        printf("Subarborele cu inaltimea mai mare: ");
        parcurgereInOrdine(subarbore);
        printf("\n");
    }
    else {
        printf("Nu exista subarbore cu inaltimea mai mare\n");
    }

    printf("Numarul de noduri in subarborele radacinii: %d\n", numaraNoduri(radacina));

    Nod* subarboreCuMaiMulteNoduri = subArboreMaiMulteN(radacina);
    if (subarboreCuMaiMulteNoduri != NULL) {
        printf("Subarborele cu mai multe noduri: ");
        parcurgereInOrdine(subarboreCuMaiMulteNoduri);
        printf("\n");
    }
    else {
        printf("Nu exista subarbore cu mai multe noduri\n");
    }

    return 0;
}
