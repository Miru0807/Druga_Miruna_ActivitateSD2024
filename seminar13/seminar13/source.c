#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodSec NodSec;
typedef struct NodP NodP;
typedef struct Autobuz Autobuz;

struct Autobuz {
	int linie;
	char* capatLinie;
};


struct NodSec {
	NodP* nod;
	NodSec* next;
};

//nodul pt lista principala

struct NodP {
	Autobuz info;
	NodP* next;
	NodSec* vecini;
};


//pt crearea grafului in mem vom crea o functie de inserare la sfarsit in lista principala
//plus o functie de cautare (dupa linie de autobuz-!!este unic numarul)
//pt lista secundara ne trebuie o functie de inserare la final
//fct de inserare a unei muchii (nodurile trebuieinserate reciproc) 1-2 si 2-1, necesar deoarece nu avem graf orientat

void inserarePrincipala(NodP** graf, Autobuz a) {
	NodP* nod = (NodP*)malloc(sizeof(NodP));
	nod->info = a; //este ok sa facem shallow copy
	nod->next = NULL;
	nod->vecini = NULL;

	if ((*graf) != NULL) {
		//nu vrem sa modificam graf (e transmis prin ref) deci luam un auxiliar
		NodP* aux=(*graf);
		while (aux->next) aux = aux->next;
		aux->next = nod;

	}
	else {
		(*graf) = nod;
	}
}

Autobuz initAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc((strlen(capat) + 1) * sizeof(char));
	strcpy(a.capatLinie, capat);

	return a;
}
NodP* cautaLinie(NodP* graf, int linie) {
	while (graf && graf->info.linie != linie) graf = graf->next;
	return graf;
}

//informatia utila e adresa la nodP
NodSec* inserareSecundara(NodSec* cap, NodP* info) {
	NodSec* nou = (NodSec*)malloc(sizeof(NodSec));
	nou->next = NULL;
	nou->nod = info;
	if (cap) {
		NodSec* p = cap;
		while (p->next) p = p->next;
		p->next = nou;


	}

	else {
		return nou;
	}

}
//graful nu se modifica, doar listele sec
void inserareMuchie(NodP* graf, int linieStart, int linieStop) {
	NodP* nodStart = cautaLinie(graf, linieStart);
	NodP* nodStop = cautaLinie(graf, linieStop);

	nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);



}
void main() {
	NodP* graf=NULL;

	//functia trebuie apelata pt toate nodurile
	inserarePrincipala(&graf, initAutobuz(0, "Romana"));
	inserarePrincipala(&graf, initAutobuz(1, "Universitate"));
	inserarePrincipala(&graf, initAutobuz(2, "Unirii"));
	inserarePrincipala(&graf, initAutobuz(3, "Victoriei"));
	inserarePrincipala(&graf, initAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);
}