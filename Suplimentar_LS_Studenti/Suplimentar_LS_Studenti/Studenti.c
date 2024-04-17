#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* nume;
	float nota;
}student;

typedef struct {
	struct nodLs* next;
	student inf;
}nodLs;

nodLs* inserare(nodLs* cap, student s) {
	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	nou->inf.cod = s.cod;
	nou->inf.nota = s.nota;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->next = NULL;
	if (cap == NULL) {
		cap = nou;
	}
	else
	{
		nodLs* aux = cap;

		while (aux->next != NULL)
		{

			aux = aux->next;
		}
		aux->next = nou;
	}
	return cap;
}

void traversare(nodLs* cap) {

	nodLs* aux = cap;
	while (aux) {
		printf("Cod=%d, Nume=%s, Nota=%5.2f", aux->inf.cod, aux->inf.nume, aux->inf.nota);
		printf("\n");
		aux = aux->next;
	}
}

void dezalocare(nodLs* cap) {
	nodLs* aux = cap;

	while (aux) {
		nodLs* temp = aux->next;
		free(aux->inf.nume);
		free(aux);
		aux = temp;
	}


}
void main() {

	int n;
	nodLs* cap = NULL;
	student s;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.nota);
		cap = inserare(cap, s);
		free(s.nume);

	}

	fclose(f);

	traversare(cap);
	dezalocare(cap);
}