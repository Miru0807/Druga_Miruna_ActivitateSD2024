#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Mail Mail;
typedef struct HEAP HEAP;
struct Mail {
    char* text;
    int prioritate;
};

struct HEAP {
    Mail* vector;
    int dim;
};

HEAP initializareHeap(int dim) {
    HEAP heap;
    heap.vector = (Mail*)malloc(sizeof(Mail) * dim);
    heap.dim = dim;
    return heap;
}

Mail initializareMesaj(const char* text, int prioritate) {
    Mail mail;
    mail.text = (char*)malloc(strlen(text) + 1);
    strcpy(mail.text, text);
    mail.prioritate = prioritate;
    return mail;
}

void afisareMail(Mail mail) {
    printf("Mailul cu textul %s si grad de prioritate %d \n", mail.text, mail.prioritate);
}

void afisareHeap(HEAP heap) {
    for (int i = 0; i < heap.dim; i++) {
        afisareMail(heap.vector[i]);
    }
}

void filtrare(HEAP heap, int pozRadacina) {
    int fs = pozRadacina * 2 + 1;
    int fd = pozRadacina * 2 + 2;

    int pozMax = pozRadacina;

    if (fs < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fs].prioritate) {
        pozMax = fs;
    }
    if (fd < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fd].prioritate) {
        pozMax = fd;
    }

    if (pozMax != pozRadacina) {
        if (heap.vector[pozRadacina].prioritate < heap.vector[pozMax].prioritate) {
            Mail aux = heap.vector[pozRadacina];
            heap.vector[pozRadacina] = heap.vector[pozMax];
            heap.vector[pozMax] = aux;

            if (pozMax < (heap.dim - 2) / 2) {
                filtrare(heap, pozMax);
            }
        }

    }
}

Mail extragereMax(HEAP* heap) {
    if (heap->dim > 0) {
        Mail extras = (*heap).vector[0];
        Mail* aux = (Mail*)malloc(sizeof(Mail) * (*heap).dim - 1);
        for (int i = 1; i < heap->dim; i++) {
            aux[i - 1] = heap->vector[i];
        }

        free(heap->vector);
        heap->vector = aux;
        heap->dim--;

        return extras; // Ad?ugat return pentru Mail extras
    }
    Mail empty = { 0 }; // Returneaz? o structur? Mail gol? dac? heap-ul este gol
    return empty;
}

void inserareMail(HEAP* heap, Mail mail) {
    Mail* aux = (Mail*)malloc(sizeof(Mail) * (*heap).dim + 1);
    aux[0] = mail;
    for (int i = 1; i < heap->dim + 1; i++) {
        aux[i] = heap->vector[i - 1];
    }
    free(heap->vector); // Corectat pentru a folosi pointerul heap
    heap->vector = aux;
    heap->dim++;

    filtrare((*heap), 0);
}

int main() { // Schimbat din void main() în int main() pentru conformitate cu standardele C
    HEAP heap = initializareHeap(6);
    heap.vector[0] = initializareMesaj("Salut1", 7);
    heap.vector[1] = initializareMesaj("Salut2", 9);
    heap.vector[2] = initializareMesaj("Salut3", 3);
    heap.vector[3] = initializareMesaj("Salut4", 8);
    heap.vector[4] = initializareMesaj("Salut5", 6);
    heap.vector[5] = initializareMesaj("Salut6", 10);

    afisareHeap(heap);

    printf("\n");
    for (int i = (heap.dim - 2) / 2; i >= 0; i--) {
        filtrare(heap, i);
    }

    afisareHeap(heap); // Corectat de la afisare la afisareHeap

    printf("\nElemente extrase: ");
    afisareMail(extragereMax(&heap)); // Ad?ugat? paranteza închis?

    printf("Inserare: ");
    inserareMail(&heap, initializareMesaj("Buna ziua!", 6));
    afisareHeap(heap); // Corectat de la afisare la afisareHeap

    return 0; // Ad?ugat pentru a indica terminarea cu succes a programului
}
