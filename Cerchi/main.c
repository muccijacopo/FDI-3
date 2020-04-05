#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************************
 ******* STRUTTURE ***********
 ****************************/

struct Punto {
	float x;
	float y;
};

struct Cerchio {
	struct Punto centro;
	float raggio;
};

struct Nodo {
	struct Cerchio c;
	struct Nodo *next;
};

/**********************************
 ****** OUTPUT DATI **************
 *******************************/
 
void stampaCerchio(struct Cerchio c) {
	printf("Centro(%.2f,%.2f) \n", c.centro.x, c.centro.y);
	printf("Raggio: %.2f \n", c.raggio);
}
 
void stampaLista(struct Nodo *nodo)
{
	if(nodo != NULL) {
		printf("\n *** LISTA CERCHI *** \n");
		while(nodo != NULL) {
			stampaCerchio(nodo->c);
			printf("\n");
			nodo = nodo->next;
		}
		printf("\n");
	}
	else
		printf("Non ci sono cerchi da stampare. \n");
}


/************************************
 ********** INPUT DATI *************
 **********************************/
 
void inserisci(struct Nodo **head, struct Cerchio c){
	struct Nodo *nuovoNodo = NULL;
	nuovoNodo = malloc(sizeof(struct Nodo));
	
	nuovoNodo->c = c;
	
	nuovoNodo->next = *head;
	*head = nuovoNodo;
}
 
void nuovoCerchio(struct Nodo **head){
	struct Cerchio c;
	// Input centro
	printf("Dimmi le coordinate del centro: \n");
	printf("Ascissa: ");
	scanf("%f", &(c.centro.x));
	printf("Ordinata: ");
	scanf("%f", &(c.centro.y));
	// Input raggio
	printf("Dimmi il valore del raggio: ");
	scanf("%f", &c.raggio);
	
	
	
	inserisci(head, c);
	printf("Cerchio aggiunto! \n");
}


/***********************************
 ********* CANCELLAMENTO **********
 **********************************/
 
void cancellaCerchio(struct Nodo **head) {
	struct Nodo *nodoCurr;
	struct Nodo *nodoPrec;
	int risposta;
	
	stampaCerchio((*head)->c);
	printf("Vuoi cancellare questo cerchio? (1 = SI; 0 = NO) ");
	scanf("%d", &risposta);
	printf("\n");
	if(risposta) {
		nodoCurr = (*head)->next;
		free(*head);
		*head = nodoCurr;
	}
	else {
		nodoCurr = (*head)->next;
		nodoPrec = *head;
		while(nodoCurr != NULL && !risposta) {
			stampaCerchio(nodoCurr->c);
			printf("Vuoi cancellare questo cerchio? (1 = SI; 0 = NO) ");
			scanf("%d", &risposta);
			printf("\n");
			
			if(risposta){
				nodoPrec->next = nodoCurr->next;
				free(nodoCurr);
			}
			else {
				nodoPrec = nodoCurr;
				nodoCurr = nodoCurr->next;
			}
		}
	}
		
	if(risposta==1)
		printf("Cerchio cancellato!\n\n");
	else
		printf("Non ho cancellato niente!\n\n");
}


/**************************************
 ********** CONTENIMENTO **********
 *********************************/
 
 float distanza(struct Punto p1, struct Punto p2) {
	 return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
 }
 
 void contenuto(struct Nodo *head) {
	 if(head != NULL && head->next != NULL) {
		 if(distanza(head->c.centro, head->next->c.centro) + head->c.raggio <= head->next->c.raggio)
			 printf("Il primo cerchio %c contenuto nel secondo. \n", 138);
		else
			printf("Il primo cerchio non %c contenuto nel secondo. \n", 138);
	 }
	else
		printf("Non ci sono abbastanza cerchi per effettuare la verifica. \n");
}




/**********************************
 ******* GESTIONE FILE ************
 **********************************/
 
struct Nodo *acquisisciFile(){
	
	struct Nodo *head = NULL;
	struct Nodo *previous;
	struct Nodo *current;
	struct Cerchio cerchio;
	int letto;
	
	FILE *fpIN = fopen("cerchi.dat", "rb");
	// Se il file è stato aperto e quindi esiste già
	if(fpIN != NULL) {
		letto = fread(&cerchio, sizeof(struct Cerchio), 1, fpIN);
		// Se c'è scritto almeno un cerchio
		if(letto) {
			head = malloc(sizeof(struct Nodo));
			head->c = cerchio;
			
			previous = head;
			
			do {
				letto = fread(&cerchio, sizeof(struct Cerchio), 1, fpIN);
				if(letto) {
					current = malloc(sizeof(struct Nodo));
					current->c = cerchio;
					
					previous->next = current;
					previous = current;
				}
				else {
					previous->next = NULL;
				}
			} 
			while(letto);
		}
	}
	
	fclose(fpIN);
	return head;
} 
 
 
void salvataggio(struct Nodo *nodo){
	FILE *fpOUT = fopen("cerchi.dat", "wb");
	while(nodo != NULL){
		fwrite(&(nodo->c), sizeof(struct Cerchio), 1, fpOUT);
		nodo = nodo->next;
	}
	
	fclose(fpOUT);
	
}

int main(int argc, char **argv)
{
	struct Nodo *head = acquisisciFile();
	int risposta = -1;
	printf("Benvenuto nel programma Cerchi! \n");
	
	while(risposta != 0){
	printf("Scegli un'opzione: \n");
	printf("1) Aggiungi un cerchio \n");
	printf("2) Cancella un cerchio a scelta \n");
	printf("3) Visualizza tutti i cerchi \n");
	printf("4) Verifica se il primo cerchio è interno al secondo \n");
	
	scanf("%d%*c", &risposta);
	
	if(risposta == 1)
		nuovoCerchio(&head);
	else if(risposta == 2) {
		if(head != NULL)
			cancellaCerchio(&head);
		else
			printf("Non ci sono cerchi da cancellare \n");
	}
	else if(risposta == 3)
		stampaLista(head);
	else if(risposta == 4)
		contenuto(head);
	else if(risposta == 0)
		printf("E' stato un piacere, i dati verrano salvati automaticamente. \n");
	else
		printf("Opzione non disponibile. \n");
		
	}

	salvataggio(head);
	
	
	
}
