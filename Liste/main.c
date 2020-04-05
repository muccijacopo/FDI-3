#include <stdio.h>
#include <stdlib.h>

struct Nodo {
		int numero;
		struct Nodo *next;
};

struct Nodo *leggiLista() {
	/* Leggi lista */
	int risposta = 0;
	printf("Inserisci una lista: \n");
	struct Nodo *head = NULL;
	
	printf("La lista ha almeno un intero? (1=SI, 0=NO): ");
	scanf("%d", &risposta);
	if(!risposta)
		printf("Ok, nessun elemento inserito.");
	else {
		struct Nodo *puntaNodo = NULL;
		puntaNodo = malloc(sizeof(struct Nodo));
		head = puntaNodo;
		printf("Inserisci il primo intero: ");
		scanf("%d", &(puntaNodo -> numero));
		printf("Ci sono altri interi? (1 = SI; 0 = NO): ");
		scanf("%d", &risposta);
		while (risposta)
		{
				puntaNodo -> next = malloc(sizeof(struct Nodo));
				puntaNodo = puntaNodo -> next;
				printf("Inserisci: ");
				scanf("%d", &(puntaNodo -> numero));
			
				printf("Ci sono altri interi? (1 = SI; 0 = NO): ");
				scanf("%d", &risposta);
		} 
	puntaNodo->next = NULL;
	}
	
	return head;
	
}

void stampaLista(struct Nodo *puntaNodo) {
	printf("La LISTA:  \n");
	while(puntaNodo != NULL) {
		printf("%d \n", puntaNodo -> numero);
		puntaNodo = puntaNodo -> next;
	}
}

void lunghezza(struct Nodo *puntaNodo) {
	int lunghezza = 0;
	
	while(puntaNodo != NULL)
	{
		lunghezza++;
		puntaNodo = puntaNodo -> next;
	}
	
	printf("La lunghezza della lista %c %d \n", 138, lunghezza);
}

int maggiore(struct Nodo *nodo1, struct Nodo *nodo2) {
	int risultato;
	if((nodo1->numero) > (nodo2->numero))
		risultato = 1;
	else
		risultato = 0;
	
	return risultato;
}

struct Nodo *massimo(struct Nodo *head) {

	struct Nodo *massimo = head;
	struct Nodo *nodo = head->next;
	
	while(nodo != NULL) {
		if(maggiore(nodo, massimo))
			massimo = nodo;
			
		nodo = nodo -> next;
	}
	
	return massimo;
}


int main(int argc, char **argv)
{
	
	struct Nodo *head = leggiLista();
	stampaLista(head);
	
	lunghezza(head);
	
	struct Nodo *numeromassimo = massimo(head);
	printf("Il numero massimo della lista %c %d", 138, numeromassimo->numero);
	
}
