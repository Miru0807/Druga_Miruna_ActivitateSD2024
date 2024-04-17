#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* denumire;
	float cantitate;
	float pret;
}produs;

typedef struct {
	struct nodLs* prev, * next;
	produs info;
}nodLs;

nodLs* inserare(nodLs* cap, nodLs** coada, produs p)
{

	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	nou->info.cod = p.cod;
	nou->info.cantitate = p.cantitate;
	nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, p.denumire);
	nou->info.pret = p.pret;
	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL) {
		cap = nou;
		*coada = cap;
	}
	else
	{
		nodLs* aux = cap;
		while (aux->next) {
			aux = aux->next;

		}
		aux->next = nou;
		aux->prev = aux;
		*coada = nou;
	}

	return cap;
}
void traversareOrdine(nodLs* cap) {
	nodLs* aux = cap;
	while (aux) {
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f", aux->info.cod, aux->info.denumire, aux->info.pret, aux->info.cantitate);
		printf("\n");
		aux = aux->next;
	}
}
void traversareInOrdine(nodLs* coada) {
	nodLs* aux = coada;
	while (aux) {
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f", aux->info.cod, aux->info.denumire, aux->info.pret, aux->info.cantitate);
		printf("\n");
		aux = aux->prev;
	}

}
void dezalocare(nodLs* cap)
{
	nodLs* aux = cap;
	while (aux) {
		nodLs* temp = aux->next;
		free(aux->info.denumire);
		free(aux);
		aux = temp;
	}
}
void conversieListaVector(nodLs* cap, produs* vect, int* nr)
{
	nodLs* temp = cap;
	while (temp != NULL)
	{
		//vect[*nr] = temp->inf;
		vect[*nr].cod = temp->info.cod;
		vect[*nr].denumire = (char*)malloc((strlen(temp->info.denumire) + 1) * sizeof(char));
		strcpy(vect[*nr].denumire, temp->info.denumire);
		vect[*nr].pret = temp->info.pret;
		vect[*nr].cantitate = temp->info.cantitate;
		(*nr)++;
		temp = temp->next;
	}
}
int main() {
	int n;
	FILE* file = fopen("fisier.txt", "r");
	if (file == NULL) {
		printf("File could not be opened.\n");
		return 1; // Exit if file not found or could not be opened
	}
	fscanf(file, "%d", &n); // Read number of products from file
	nodLs* cap = NULL, * coada = NULL;
	produs p;
	char buffer[256]; // Ensure buffer is large enough for the strings

	for (int i = 0; i < n; i++)
	{
		fscanf(file, "%d", &p.cod);
		fscanf(file, "%s", buffer); // Assumes no spaces in the product name
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(file, "%f", &p.pret);
		fscanf(file, "%f", &p.cantitate);

		cap = inserare(cap, &coada, p);

		free(p.denumire); // Freeing here after insertion, as it gets copied in inserare
	}
	fclose(file); // Always close the file after done using

	traversareOrdine(cap);
	traversareInOrdine(coada);
	produs* vect = (produs*)malloc(n * sizeof(produs));
	int nr = 0;
	printf("\nConversie\n");
	conversieListaVector(cap, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f", vect[i].cod, vect[i].denumire, vect[i].pret, vect[i].cantitate);
	dezalocare(cap);
	return 0;
}

