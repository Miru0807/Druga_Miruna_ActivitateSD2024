#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct Masina {
	int id;
	char* producator;
	int nr_usi;
	float pret;
};

struct Masina* inserareVector(struct Masina* vec_m, int* dim, struct Masina m) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*dim) + 1));
	for (int i = 0; i < (*dim); i++) {
		aux[i] = vec_m[i]; //shallow copy
	}
	aux[(*dim)] = m;
	(*dim)++;

	if (vec_m != NULL) {
		free(vec_m);
	}

	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* dim) {
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("Fisierul nu exista.\n");
		return NULL;
	}

	struct Masina* vec_m = NULL;
	(*dim) = 0;

	char buffer[100];
	char delimiter[] = ",\n";
	while (fgets(buffer, 100, f) != NULL) {
		//id
		char* token = strtok(buffer, delimiter); //util ca ",\n" sa fie o variabila pentru a putea modifica toate utilizarile sale simultan

		struct Masina m;
		m.id = atoi(token);

		//prod
		token = strtok(NULL, delimiter);
		m.producator = (char*)malloc(strlen(token) + 1);
		strcpy(m.producator, token);

		//nr_usi
		token = strtok(NULL, delimiter);
		m.nr_usi = atoi(token);

		//pret
		token = strtok(NULL, delimiter);
		m.pret = atof(token);

		vec_m = inserareVector(vec_m, dim, m);
	}

	fclose(f);
	return vec_m;
}

//seminar 4

void citireMatriceFisier(const char* numeFisier, struct Masina** mat_m, int nr_linii, int* nr_col) {
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("Fisierul nu exista.\n");
	}
	else {

		char buffer[100];
		char delimiter[] = ",\n";

		while (fgets(buffer, 100, f) != NULL) {
			//id
			char* token = strtok(buffer, delimiter); //util ca ",\n" sa fie o variabila pentru a putea modifica toate utilizarile sale simultan

			struct Masina m;
			m.id = atoi(token);

			//prod
			token = strtok(NULL, delimiter);
			m.producator = (char*)malloc(strlen(token) + 1);
			strcpy(m.producator, token);

			//nr_usi
			token = strtok(NULL, delimiter);
			m.nr_usi = atoi(token);

			//pret
			token = strtok(NULL, delimiter);
			m.pret = atof(token);

			mat_m[m.nr_usi - 2] = inserareVector(mat_m[m.nr_usi - 2], &(nr_col[m.nr_usi - 2]), m);
		}

		fclose(f);
	}
}

void afisareMatrice(struct Masina** mat_m, int nr_linii, int* nr_col) {
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_col[i]; j++) {
			printf("%d, %s, %d, %5.2f\t", mat_m[i][j].id, mat_m[i][j].producator, mat_m[i][j].nr_usi, mat_m[i][j].pret);
		}
		printf("\n");
	}
}

float pretMediu(struct Masina** mat_m, int nr_linii, int* nr_col, int nr_usi) {
	float pret_total = 0;
	if (nr_usi < 2 || nr_usi > 4) {
		printf("Numar de usi invalid.\n");
		return -1;
	}

	int index = nr_usi - 2;

	if (nr_col[index] == 0) {
		printf("Nu exista masini cu acest numar de usi in matrice.\n");
		return -1;
	}

	for (int i = 0; i < nr_col[index]; i++) {
		pret_total += mat_m[index][i].pret;
	}

	return pret_total / nr_col[index];

}

struct Masina findByID(struct Masina** mat_m, int nr_linii, int* nr_col, int id) {
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_col[i]; j++) {
			if (mat_m[i][j].id == id) {
				return mat_m[i][j];
			}
		}
	}

	struct Masina m;
	m.id = -1;
	m.producator = (char*)malloc(strlen("Anonim") + 1);
	strcpy(m.producator, "Anonim");
	m.nr_usi = -1;
	m.pret = -1;

	printf("Nu a fost gasita o masina cu ID-ul introdus.\n");
	return m;

}

void dezalocareMatrice(struct Masina*** mat_m, int nr_linii, int** nr_col) {
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < (*nr_col)[i]; j++) {
			free((*mat_m)[i][j].producator);
			(*mat_m)[i][j].producator = NULL;
		}
		free((*mat_m)[i]);
		(*mat_m)[i] = NULL;
	}
	free((*nr_col));
	free((*mat_m));

	(*nr_col) = NULL;
	(*mat_m) = NULL;

	printf("Matricea a fost dezalocata.\n");
}

int main() {


	struct Masina** mat_m = NULL;
	int nr_linii = 3;
	int* nr_col;

	nr_col = (int*)malloc(sizeof(int) * nr_linii);
	mat_m = (struct Masina**)malloc(sizeof(struct Masina*) * nr_linii);
	for (int i = 0; i < nr_linii; i++) {
		nr_col[i] = 0;
		mat_m[i] = NULL;
	}

	citireMatriceFisier("masini.txt", mat_m, nr_linii, nr_col);
	//afisareMatrice(mat_m, nr_linii, nr_col);

	int nr_usi = 4;
	printf("Pretul mediu a masinilor cu %d usi este %.2f\n", nr_usi, pretMediu(mat_m, nr_linii, nr_col, nr_usi));

	struct Masina m_byID = findByID(mat_m, nr_linii, nr_col, 1);
	printf("%d, %s, %d, %5.2f\n", m_byID.id, m_byID.producator, m_byID.nr_usi, m_byID.pret);

	dezalocareMatrice(&mat_m, nr_linii, &nr_col);

	return 0;
}