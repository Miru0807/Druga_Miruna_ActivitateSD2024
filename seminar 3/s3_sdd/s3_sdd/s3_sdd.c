#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini)
{
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++)
	{
		aux[i] = masini[i];
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;
	if (masini != NULL)
		free(masini);  //fara for pentru ca aux[i] = masini[i] e shallow copy
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini)
{
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char separator[] = ",\n";
	struct Masina* masini = NULL;
	*nrMasini = 0;
	while (fgets(buffer, 100, file) != NULL)
	{
		char* token = strtok(buffer, separator);
		struct Masina m;
		m.id = atoi(token);
		token = strtok(NULL, separator);
		m.producator = (char*)malloc(strlen(token) + 1);
		strcpy(m.producator, token);
		token = strtok(NULL, separator);
		m.nrUsi = atoi(token);
		token = strtok(NULL, separator);
		m.pret = atof(token);
		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(file);
	return masini;
}

int main()
{
	int nrMasini;
	struct Masina* masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		printf("\n%d. Masina produsa de %s are %d usi si costa %5.2f lei", masini[i].id, masini[i].producator, masini[i].nrUsi, masini[i].pret);
	}
	return 0;
}