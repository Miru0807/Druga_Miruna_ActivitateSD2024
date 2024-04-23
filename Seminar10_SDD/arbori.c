#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stddef.h>
#include<stddef.h>

//azi facem arbori binari de cautare
//structura rezervare restaurant
//ce treb sa contina un nod? fiu de stanga si fiu de dreapta

typedef struct Rezervare Rezervare;
struct Rezervare {
	int id;
	char* numeClient;
	int nrPersoane;
};

typedef struct Nod Nod;
struct Nod {
	Rezervare info;
	Nod* st;
	Nod* dr;
};

Rezervare citireRezervare(FILE* f) {
	Rezervare r;
	char aux[30];
	fgets(aux, 30, f);
	fscanf(f, "%d", &(r.id)); //se da adresa lui r.id
	//am folosi fgets daca am avea si spatii
	fscanf(f, "%s", &aux);
	r.numeClient = (char*)malloc(strlen(aux) + 1);
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &(r.nrPersoane));
	return r;

}

//ne vom folosi de id pt comparatie
Nod* inserareArbore(Nod* arbore, Rezervare rez) {
	if (arbore != NULL)//verificam ca radacina sa nu fie nula
	{
		if (arbore->info.id < rez.id) {
			arbore->dr = inserareArbore(arbore->dr, rez);
		}
		else {
			arbore->st = inserareArbore(arbore->st, rez);
		}
	}
	else {
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = rez;//shallow copy
		temp->st = NULL;
		temp->dr = NULL;

		arbore = temp;
	}

	return arbore;
}

void citireFisier(const char* numeFisier, Nod** radacina) {
	FILE* f = fopen(numeFisier, "r");
	int nr;
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++) {
		Rezervare r;
		r = citireRezervare(f);
		(*radacina) = inserareArbore((*radacina), r);

	}


}




//exista 3 moduri de a parcurge un arbore: radacina stanga-dreapta, stanga-dreapta radacina, stanga radacina dreapta, 
// sau PREORDINE, POSTORDINE, INORDINE

void afisareRezervare(Rezervare r) {
	printf("#%d, Rezervare pentru %s de %d persoane\n", r.id, r.numeClient, r.nrPersoane);
}

void afisareArborePreordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareRezervare(arbore->info);
		afisareArborePreordine(arbore->st);
		afisareArborePreordine(arbore->dr);
	}
}


void afisareArboreInordine(Nod* arbore) {
	if (arbore != NULL)
	{
		/*afisareRezervare(arbore->st->info);*/ //fara asta
		afisareArboreInordine(arbore->st);
		afisareRezervare(arbore->info);
		afisareArboreInordine(arbore->dr);

	}

}

Rezervare cautaRezervareDupaId(Nod* radacina, int id) {
	if (radacina != NULL) {
		if (radacina->info.id < id) {
			return cautaRezervareDupaId(radacina->dr, id);
		}
		else {
			if (radacina->info.id > id)
			{
				return cautaRezervareDupaId(radacina->st, id);
			}
			else {
				return radacina->info;
			}
		}
	}
	else {
		Rezervare r;
		r.id = -1;
		r.numeClient = NULL;
		r.nrPersoane = -1;
		return r;
	}
}

void afisareArborePostordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareArborePostordine(arbore->st);
		afisareArborePostordine(arbore->dr);
		afisareRezervare(arbore->info);
	}
}

int calculNumarTotalDePersoane(Nod* rad) {
	if (rad != NULL) {
		int rPersoane = rad->info.nrPersoane;
		int sPersoane = calculNumarTotalDePersoane(rad->st);
		int dPersoane = calculNumarTotalDePersoane(rad->dr);
		int suma = rPersoane + sPersoane + dPersoane;
		return suma;
	}
	else {
		return 0; //aici se face practic initializarea lui suma cu 0
	}
}

void main() {
	Nod* radacina = NULL;
	citireFisier("Rezervari.txt", &radacina);
	//afisareArborePreordine(radacina);
	//afisareArboreInordine(radacina);
	//parcurgerea in inordine va sortaelementele in ordine crescatoare <=> sortarea binara
	//afisareArborePostordine(radacina);
	Rezervare r;
	r = cautaRezervareDupaId(radacina, 10);
	printf("Rezervarea cautata: ");
	afisareRezervare(r);
	printf("\n");

	printf("Numar total persoane : %d", calculNumarTotalDePersoane(radacina));

}


