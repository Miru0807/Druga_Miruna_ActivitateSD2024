#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct {

	int cod;
	char* nume;
	float medie;
}student;

typedef struct {
	student info;
	struct nodLs* next;
	struct nodLs* prev;
}nodLs;

nodLs* inserare(nodLs* cap, nodLs** coada, student s) {

	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	nou->info.cod = s.cod;
	nou->info.medie = s.medie;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);

	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL) {
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodLs* aux = cap;
		while (aux->next != NULL) {
			aux = aux->next;

		}
		aux->next = nou;
		nou->prev = aux;
		*coada = nou;
	}
	return cap;
}
void traversareOrdine(nodLs* cap) {

	nodLs* aux = cap;
	while (aux) {
		printf("Cod=%d, Nume=%s, Medie=%5.2f", aux->info.cod, aux->info.nume, aux->info.medie);
		printf("\n");
		aux = aux->next;
	}
}
void traversareInversa(nodLs* coada) {
	nodLs* aux = coada;
	while (aux) {
		printf("Cod=%d, Nume=%s, Medie=%5.2f", aux->info.cod, aux->info.nume, aux->info.medie);
		printf("\n");
		aux = aux->prev;
	}
}

void dezalocare(nodLs* cap) {
	nodLs* aux = cap;
	while (aux) {
		nodLs* temp = aux->next;
		free(aux->info.nume);
		free(aux);
		aux = temp;
	}
}
void main() {

	int n;
	student s;
	char buffer[20];
	nodLs* cap = NULL;
	nodLs* coada = NULL;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {

		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		cap = inserare(cap, &coada, s);
		free(s.nume);
	}
	fclose(f);
	traversareOrdine(cap);
	printf("\nInversa\n");
	traversareInversa(coada);

	dezalocare(cap);
}