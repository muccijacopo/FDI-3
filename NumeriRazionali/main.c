#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Razionale {
	int num;
	int den;
};

struct Nodo {
	struct Razionale n;
	struct Nodo *next;
};

/********************************
 ********* STAMPE *************
 *******************************/
void stampaNumero(struct Razionale n) {
	if(n.num != 0) {
		if(n.den != 1)
			printf("- %d/%d \n", n.num, n.den);
		else 
			printf("- %d \n", n.num);
	}
	else 
		printf("- 0 \n");
	
}
void stampaLista(struct Nodo *lista) {
	if(lista != NULL) {
		printf("*** LISTA NUMERI RAZIONALI *** \n");
		while(lista != NULL) {
			stampaNumero(lista->n);
			lista = lista->next;
			printf("\n");
		}
	}
	else 
		printf("La lista %c vuota \n", 138);
}

/*********************************
 ********* INSERIMENTO ***********
 **********************************/
void inserisci(struct Nodo **head, struct Razionale numero) {
	struct Nodo *nuovoNodo = malloc(sizeof(struct Nodo));
	nuovoNodo->n = numero;
	
	nuovoNodo->next = *head;
	*head = nuovoNodo;
	printf("Numero aggiunto alla lista \n");
}

void nuovoNumero(struct Nodo **head) {
	struct Razionale numero;
	
	printf("Inserisci il numeratore: ");
	scanf("%d", &numero.num);
	printf("Inserisci il denominatore: ");
	scanf("%d", &numero.den);
	
	inserisci(head, numero);
}

/***************************************
 ************ CANCELLAMENTO ***********
 ************************************/
void cancellaNumero(struct Nodo **head) {
	struct Nodo *nodo;
	struct Nodo *nodoPrec;
	
	if(*head != NULL) {
		if((*head)->next == NULL) {
			free(*head);
			*head = NULL;
		}
		else {
			nodo = (*head)->next;
			nodoPrec = *head;
			while(nodo->next != NULL){
				nodoPrec = nodo;
				nodo = nodo->next;
			}
			
			free(nodo);
			nodoPrec->next = NULL;
		}
		
		printf("Numero cancellato. \n");
	}
	else
		printf("Nessun numero da cancellare. \n");
}

/******************************************
 ************* ORDINAMENTO ************
 **************************************/
int precede(struct Razionale n1, struct Razionale n2) {
	float r1 = (float)n1.num / (float)n1.den;
	float r2 = (float)n2.num / (float)n2.den;
	return r1 < r2;
} 

void ordina(struct Nodo *head) {
	struct Nodo *primo;
	struct Nodo *minimo;
	struct Nodo *nodo;
	struct Razionale temp;
	
	if(head != NULL) {
		if(head->next != NULL) {
			primo = head;
			while(primo->next != NULL) {
				minimo = primo;
				for(nodo = primo->next; nodo!=NULL; nodo = nodo->next) {
					if(precede(nodo->n, minimo->n))
						minimo = nodo;
				}
				
				temp = primo->n;
				primo->n = minimo->n;
				minimo->n = temp;
				
				primo = primo->next;
				
			}
			printf("Lista ordinata. \n");
		}
		else
			printf("Non ci sono abbastanza elementi da poterli ordinare. \n");
	}
	else printf("La lista %c vuota! \n");
}

struct Razionale riduzioneMinimiTermini(struct Razionale n) {
	
	struct Razionale ridotto;
	int mcd = n.den;
	
	while(n.num % mcd != 0 || n.den % mcd != 0) {
		mcd--;
	}
	
	ridotto.num = n.num / mcd;
	ridotto.den = n.den / mcd;
	
	return ridotto;
	
}


void riduzione(struct Nodo *lista) {
	struct Razionale ridotto;
	if(lista != NULL) {
		while(lista != NULL) {
			ridotto = riduzioneMinimiTermini(lista->n);
			lista->n = ridotto;
			lista = lista->next;
		}
	}
	else 
		printf("Non ci sono numeri razionali nella lista! \n");
}

/*********************************
 ***** GESTIONE FILE ************
 *******************************/
struct Nodo *acquisisci() {
	struct Nodo *head = NULL;
	struct Nodo *nodoCurr;
	struct Nodo *nodoPrec;
	struct Razionale numero;
	int letto = 0;
	
	FILE *fpIN = fopen("razionali.dat", "rb");
	if(fpIN != NULL) {
		letto = fread(&numero, sizeof(struct Razionale), 1, fpIN);
		if(letto) {
			head = malloc(sizeof(struct Nodo));
			head->n = numero;
			
			nodoPrec = head;
			
			do {
				letto = fread(&numero, sizeof(struct Razionale), 1, fpIN);
				if(letto){
					nodoCurr = malloc(sizeof(struct Nodo));
					nodoCurr->n = numero;
					
					nodoPrec->next = nodoCurr;
					nodoPrec = nodoCurr;
				}
				else 
					nodoPrec->next = NULL;
			}
			while(letto);
		}
	}
	
	return head;
}


void salvataggio(struct Nodo *lista) {
	FILE *fpOUT = fopen("razionali.dat", "wb");
	if(fpOUT != NULL) {
		while(lista != NULL) {
			fwrite(&(lista->n), sizeof(struct Razionale), 1, fpOUT);
			lista = lista->next;
		}
		printf("Salvataggio effettuato. \n");
	}
	else
		printf("Impossibile effettuare il salvataggio. \n");
}

int main(int argc, char **argv)
{
	struct Nodo *head = acquisisci();
	int risposta = -1;
	
	printf("Benvenuto nel programma di gestione numeri razionali \n");
	
	while(risposta != 0) {
		printf("Scegli un'opzione: \n");
		printf("1) Aggiungi un numero razionale alla lista \n");
		printf("2) Cancella l'ultimo numero della lista \n");
		printf("3) Visualizza la lista \n");
		printf("4) Ordina la lista \n");
		printf("5) Riduzione ai minimi termini \n");
		printf("0) Salva ed esci. \n");
		scanf("%d", &risposta);
		
		
		if(risposta == 1)
			nuovoNumero(&head);
		else if(risposta == 2)
			cancellaNumero(&head);
		else if(risposta == 3)
			stampaLista(head);
		else if(risposta == 4)
			ordina(head);
		else if(risposta == 5)
			riduzione(head);
	}
	
	
	salvataggio(head);
	return 0;
}
