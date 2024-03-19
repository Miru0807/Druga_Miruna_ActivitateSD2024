#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdio.h>

//Liste simplu inlantuite = 
//diferenta dintre lista si vector,
//lista op parcurgem element cu element, la vector avem acces direct pt ca ocupa o memorie contigua


//2 moduri de inserare in lista, la inceput si la sfarsit
//prin ce identificam o lista? raspuns: printr-un pointer catre adresa primului nod(capul listei)

typedef struct Santier Santier; //definirea unui alias
typedef struct Nod Nod;

struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

struct Nod {
	Santier santier;
	Nod* next;
};


Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(strlen(numeProiect)+1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;
	return santier;
}

//functie care sa insereze un santier intr-o lista

Nod* inserareInceput(Santier santier, Nod* lista) {
	//ne cream un nou nod, inserarea se face la inceput
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->santier = santier;
	nod->next = lista;
	return nod;
}

//o functie care sa-mi afiseze aceasta lista

void afisareSantier(Santier santier)
{
	printf("Santierul %s are %d muncitori si %5.2f m^2 suprafata.\n",
		santier.numeProiect,
		santier.nrMuncitori,
		santier.suprafata);
}

//calculam suma nr de muncitori, C si C++ sunt keysensitive
int sumaMuncitori(Nod* lista)
{
	int Suma = 0;
	while (lista != NULL)
	{
		Suma = Suma + lista->santier.nrMuncitori;
		lista = lista->next;
	}
	return Suma;
}


void afisareLista(Nod* lista)
{
	while (lista != NULL)
	{
		//procesare, apelam functia de afisare, poate sa constea in orice
		afisareSantier(lista->santier);

		lista = lista->next; //parcurgerea clasica
	}

}

//facem o functie de stergere a listei

void stergereLista(Nod** lista) {
	while ((*lista) != NULL) {
		free((*lista)->santier.numeProiect);//am sters numele proiectului
		//nodul mai trebuie sters
		Nod* aux;
		aux = (*lista)->next;
		//treb sa facem distinctia dintre obiect si pointer
		free(*lista);//pointeaza catre o lista in care nu mai am nimic
		(*lista) = aux;
	}
	(*lista) = NULL;
}
//numele santierului cu densitatea cea mai mare de muncitori pe m^2

float densitateMuncitori(Santier santier) {
	if (santier.suprafata > 0) {
		return santier.nrMuncitori /
			santier.suprafata;
	}
	else return 0;
}

char* numeSantierDensitateMaxima(Nod* lista) {
	float max = 0;
	char* aux= NULL;
	while (lista != NULL) {
		if (densitateMuncitori(lista->santier) > max)
		{
			max = densitateMuncitori(lista->santier);
			aux = lista->santier.numeProiect;
		}
		lista = lista->next;
	}
	if (aux != NULL) {
		char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
		strcpy(numeProiectDensitate, aux);
		return numeProiectDensitate;
	}
	else return NULL;
	
}

int main() {
	Nod* lista = NULL;
	Santier s1 = initializareSantier("Santier 1", 10, 300);
	Santier s2 = initializareSantier("Santier 2", 11, 350);
	Santier s3 = initializareSantier("Santier 3", 12, 400);
	Santier s4 = initializareSantier("Santier 4", 15, 200);
	lista = inserareInceput(s1, lista);
	lista = inserareInceput(s2, lista);
	lista = inserareInceput(s3, lista);
	lista = inserareInceput(s4, lista);
	lista = inserareInceput(initializareSantier("Santier 5", 10, 34), lista);
	afisareLista(lista);
	int suma = 0;
	suma = sumaMuncitori(lista);
	printf("Suma este %d", suma);
	stergereLista(&lista);
	afisareLista(lista);
	printf("\n%s\n", numeSantierDensitateMaxima(lista));
	stergereLista(&lista);
	afisareLista(lista);
}

//tema: treb sa stergem un nod, mai ales daca e la mijloc sa stim sa facem legatura