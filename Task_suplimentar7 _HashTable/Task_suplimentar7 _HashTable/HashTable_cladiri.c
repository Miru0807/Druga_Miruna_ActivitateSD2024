/*Se doreste gestiunea cladirilor din Bucuresti in funtie de anul construirii. Acest lucru va ajuta la stabilire riscului seismic al acestora.
1. Sa se creeze o tabela de dispersie pentru stocarea cladirilor din Bucuresti 
(structura Cladire contine ce atribute vreti voi dar va contine obligatoriu anul construirii si un id unic). campul folosit pentru clusterizare este anul construirii cladirii.
2. Implementati o functie care afiseaza cladirile dintr-un cluster 
(construite intr-un an primit ca parametru).
3. Implementati o functie care sterge o cladire pentru care se primeste id-ul si anul construirii. 
4. Implementati o functie care sterge o cladire pentru care se primeste doar id-ul cladirii. 
5. Observatii diferenta dintre functia implementata la 4 si functia de la 5.
6. Implementati o functie care salveaza intr-un vector toate  cladirile dintr-un an primit ca parametru. 
Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din tabela de dispersie. Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.
7. Implementati o functie care modifica anul construirii unei cladiri identificate prin ID. 
Functia primeste ca parametri: id-ul cladirii, vechiul an de constructie si noul an de constructie. Aveti grija se modifica valoarea atributului folosit pentru clusterizare.*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Cladire {
	int nrCladire; 
	char* strada;
	int nr_ap;
	int etaje; 
	int an;
};

struct ListNode {
	struct ListNode* next; 
	struct Cladire* info;
};

struct HashTable {
	struct ListNode** buckets; 
	int size;
	int noEl;
};

struct Cladire* createCladire(int nrb, const char* strada, unsigned int nra, unsigned int etaje, unsigned int an) 
{
	struct Cladire* cl = (struct Cladire*)malloc(sizeof(struct Cladire)); 
	cl->nrCladire = nrb; 
	cl->strada = (char*)malloc(strlen(strada) + 1);
	strcpy(cl->strada, strada);
	cl->nr_ap = nra;
	cl->etaje = etaje; 
	cl->an = an;
	return cl; 
}

struct ListNode* createNode(struct Cladire* b) { 

	struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode)); 
	node->next = NULL;
	node->info = b;
	return node;
}

void insertNode(struct ListNode* list, struct ListNode* node) 
{
	if (list != NULL)
		node->next = list;
	list = node;
}

void createHash(struct HashTable ht, int size) 
{
	ht.buckets = (struct ListNode**)malloc(sizeof(struct ListNode*) * size); 
	memset(ht.buckets, NULL, sizeof(struct ListNode*) * size); 
	ht.size = size;
	ht.noEl = 0;
}

int fhash(const char* key, int dim)
{
	int index = key[0] % dim;
	return index;
}

void insertHT(struct HashTable* ht, struct Cladire* b) 
{
	int index = fhash(b->strada, ht->size);
	struct ListNode* node = createNode(b); 
	struct ListNode* list = ht->buckets[index];
	insertNode(list, node);
	ht->buckets[index] = list;
	ht->noEl++;
}

int nrCladiri(struct HashTable ht, unsigned int an) 
{
	int nr = 0;
	for (int i = 0; i < ht.size; i++)
	{
		struct ListNode* list = ht.buckets[i]; 
		while (list)
		{
			if (list->info->an > an)
				nr++;
			list = list->next;
		}
	}
	return nr;
}

void createList(struct HashTable ht, struct ListNode* head, const char* strada) 
{
	int index = fhash(strada, ht.size);
	struct ListNode* list = ht.buckets[index]; 
	while (list)
	{
		if (strcmp(list->info->strada, strada) == 0)
		{
			struct ListNode* node = createNode(list->info); 
			insertNode(head, node);
		}
		list = list->next;
	}
}

void changeKey(struct HashTable ht, const char* oldKey, const char* newKey) 
{
	int index = fhash(oldKey, ht.size);
	struct Cladire* b = NULL; 
	struct ListNode* list = ht.buckets[index]; 
	while (list && strcmp(list->info->strada, oldKey) == 0) 
	{
		b = createCladire(list->info->nrCladire, newKey, list->info->nr_ap, list->info->etaje, list->info->an); // Fixed function name and parameters
		insertHT(&ht, b);
		struct ListNode* temp = list; 
		list = list->next; 
		free(temp->info->strada); 
		free(temp->info); 
		free(temp); 
		
	}
	ht.noEl--; 
}

void main()
{
	struct Cladire* c1 = createCladire(1, "Str1", 50, 10, 2019); 
	struct Cladire* c2 = createCladire(2, "Str1", 48, 5, 2020);
	struct Cladire* c3 = createCladire(3, "Str1", 10, 3, 2018);
	struct Cladire* c4 = createCladire(4, "Bd1", 55, 10, 2017);
	struct Cladire* c5 = createCladire(5, "Bd1", 20, 7, 2016);

	struct HashTable ht; 
	createHash(ht, 5);
	insertHT(&ht, c1);
	insertHT(&ht, c2);
	insertHT(&ht, c3);
	insertHT(&ht, c4);
	insertHT(&ht, c5);

	printf("%d\n", nrCladiri(ht, 2018)); 
	struct ListNode* head = NULL;
	createList(ht, head, "Str1");
	while (head)
	{
		printf("\n%d, %s, %d, %d, %d", head->info->nrCladire, head->info->strada, head->info->nr_ap, head->info->etaje, head->info->an); // Fixed field names
		head = head->next;
	}
}
