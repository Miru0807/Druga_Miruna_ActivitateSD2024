#include<stdio.h>
#include<malloc.h>


struct Cofetarie {
	//o structura este colectie neomogena de date, o clasa care nu poate sa aiba metode, 
	//este o struct neomogena care contine doar atribute, caracteristicile unei cofetarii
	char* nume;
	int nrAngajati;
	float* salarii;
};


//o functie care ne va arata o cofetarie
void afiseazaCofetarie(struct Cofetarie c) {
	if (c.nume != NULL) {
		printf("Nume: %s/n");
	}
	printf("Nume: %s/n", c.nume);
	printf("Numar angajati: %d:/n", c.nrAngajati);
	printf("Salarii: ");
	for (int i = 0; i < c.nrAngajati; i++) {
		printf("%5.2f,", c.salarii[i]);
	}
	printf("/n");
}

struct Cofetarie initializareCofetarie(const char* nume, int nrAngajati, const float* salarii) {
	struct Cofetarie c;
	c.nume = malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrAngajati = nrAngajati;
	c.salarii = malloc(sizeof(float) * nrAngajati);
	for (int i = 0; i < nrAngajati; i++)
	{
		c.salarii[i] = salarii[i];
	}
	return c;
}

void stergeCofetarie(struct Cofetarie* c) {
	if (c->nume != NULL) {
		free(c->nume);
	}
	free(c->salarii);
	c->nume = NULL;
	c->salarii = NULL;
}
int main() {
	// de ce functia main este de tip int? 
	//cum ne declaram un obiect de tipul cofetarie?
	struct Cofetarie cofetarie1;
	//cum initializam fiecare atribut in parte?
	//Dulce-numele cofetariei, sizeof este o functie
	cofetarie1.nume = (char*)malloc(strlen("Dulce") + 1);
	strcpy(cofetarie1.nume, "Dulce");
	cofetarie1.nrAngajati = 3;
	//cast implicit sau explicit
	cofetarie1.salarii = malloc(sizeof(float) * cofetarie1.nrAngajati);
	for (int i = 0; i < cofetarie1.nrAngajati;i++)
	{
		cofetarie1.salarii[i] = (i + 1) * 1000;
	}


	afiseazaCofetarie(cofetarie1);
	float* vector = malloc(sizeof(float) * 2);
	vector[0] = 4567;
	vector[1] = 3456;
	struct Cofetarie cofetarie2 = initializareCofetarie("Mara", 2, vector);
	afiseazaCofetarie(cofetarie2);

	free(vector);
	stergeCofetarie(&cofetarie2);
	afisareCofetarie(cofetarie2);

	free(cofetarie2.nume);
	free(cofetarie2.salarii);

	free(cofetarie1.nume);
	free(cofetarie1.salarii);

	//punctele dupa Format inseamna o fct cu nr variabil de parametrii, depinde ff mult de acest format(%=1 parametru, %%=2 parametrii)
//malloc= o functie, primeste param dimensiunea exprimata in bytes sau octeti, returneaza un pointer catre o adresa de memorie, imi returneaza un pointer


	return 0;
}