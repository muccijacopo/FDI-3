#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Punto {
	float x;
	float y;
};

struct Segmento {
	struct Punto p1;
	struct Punto p2;
};

struct Nodo {
	struct Segmento s;
	struct Nodo *next;
};

/***********************************
 ******* FUNZIONI GEOMETRICHE *****
 ***********************************/
float lunghezza(struct Punto p1, struct Punto p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

float coefficiente(struct Punto p1, struct Punto p2) {
	return (p2.y-p1.y)/(p2.x-p1.x);
}

void verificaPerpendicolari(struct Nodo *head) {
	float c1, c2;
	c1 = coefficiente(head->s.p1, head->s.p2);
	c2 = coefficiente(head->next->s.p1, head->next->s.p2);
	
	if((c1*c2) == -1)
		printf("I primi due segmenti sono perpendicolari. \n");
	else
		printf("I primi due segmenti non sono perpendicolari. \n");
}

void verificaParalleli(struct Nodo *lista) {
	int scelta = 0;
	int risposta = 0;
	float c1, c2;
	
	printf("Scegli i segmenti da verificare: \n");
	while(scelta < 1 && lista != NULL) {
		stampaSegmento(lista->s);
		printf("Vuoi verificare questo segmento? (1 = SI; 0 = NO): ");
		scanf("%d", &risposta);
		if(risposta) {
			scelta++;
			c1 = coefficiente(lista->s.p1, lista->s.p2);
		}
		lista = lista->next;
	}
	
	while(scelta < 2 && lista != NULL) {
		stampaSegmento(lista->s);
		printf("Vuoi verificare questo segmento? (1 = SI; 0 = NO): ");
		scanf("%d", &risposta);
		if(risposta) {
			scelta++;
			c2 = coefficiente(lista->s.p1, lista->s.p2);
		}
		lista = lista->next;
	}
	
	if(scelta < 2) {
		printf("Devi scegliere due segmenti! \n");
	}
	else {
		if(c1 == c2)
			printf("I due segmenti sono paralleli. \n");
		else
			printf("I due segmenti non sono paralleli. \n");
	}
	
	
}

/*************************************
 ************ STAMPE ****************
 **********************************/
 
void stampaSegmento(struct Segmento s) {
	printf("Primo estremo: (%.2f,%.2f) \n", s.p1.x, s.p1.y);
	printf("Secondo estremo: (%.2f,%.2f) \n", s.p2.x, s.p2.y);
	printf("Lunghezza: %.2f \n", lunghezza(s.p1, s.p2));
}
void stampaLista(struct Nodo *lista) {
	if(lista != NULL) {
		while(lista != NULL) {
			stampaSegmento(lista->s);
			printf("---- \n");
			lista = lista->next;
		}
	}
	else {
		printf("Non ci sono segmenti nella lista. \n");
	}
}


/**************************************
 ********** INSERIMENTI ***************
 *************************************/
void inserisci(struct Nodo **head, struct Segmento segmento) {
	struct Nodo *nuovoNodo = NULL;
	nuovoNodo = malloc(sizeof(struct Nodo));
	
	nuovoNodo->s = segmento;
	
	nuovoNodo->next = *head;
	*head = nuovoNodo; // Nuova testa
}

void nuovoSegmento(struct Nodo **head) {
	struct Segmento s;
	
	printf("Inserisci i due estremi: \n");
	//Inserimento primo estremo
	printf("Primo estremo: \n");
	printf("- X: ");
	scanf("%f", &s.p1.x);
	printf("- Y: ");
	scanf("%f", &s.p1.y);
	// Inserimento secondo estremo
	printf("Secondo estremo: \n");
	printf("- X: ");
	scanf("%f", &s.p2.x);
	printf("- Y: ");
	scanf("%f", &s.p2.y);
	
	inserisci(head, s);
	
}

/************************
 ******* CANCELLAZIONI ***
 **************************/
 
void cancellaSegmento(struct Nodo **head) {
	struct Nodo *newHead;
	
	if(*head != NULL) {
		newHead = (*head)->next;
		free(*head);
		*head = newHead;
		printf("Segmento cancellato. \n");
	}
	else
		printf("Non ci sono segmenti da cancellare! \n");
}


/*********************************
 ******* GESTIONE FILE *********
 ********************************/

struct Nodo *acquisizione() {
	struct Nodo *head = NULL;
	struct Nodo *nodoCurr;
	struct Nodo *nodoPrec;
	struct Segmento segmento;
	int letto = 0;
	
	FILE *fpIN = fopen("segmenti.dat", "rb");
	if(fpIN != NULL) {
		letto = fread(&segmento, sizeof(struct Segmento), 1, fpIN);
		if(letto){
			head = malloc(sizeof(struct Nodo));
			head->s = segmento;
			
			nodoPrec = head;
			
			do {
				letto = fread(&segmento, sizeof(struct Segmento), 1, fpIN);
				if(letto){
					nodoCurr = malloc(sizeof(struct Nodo));
					nodoCurr->s = segmento;
					
					nodoPrec->next = nodoCurr;
					nodoPrec = nodoCurr;
				}
			}
			while(letto);
		}
	}
	
	fclose(fpIN);
	return head;
	
}


void salvataggio(struct Nodo *lista) {
	FILE *fpOUT = fopen("segmenti.dat", "wb");
	while(lista != NULL){
		fwrite(&lista->s, sizeof(struct Segmento), 1, fpOUT);
		lista = lista->next;
	}
}

/**********************************
 ****** FUNZIONE PRINCIPALE *******
 ***********************************/
int main(int argc, char **argv)
{
	int risposta = -1;
	struct Nodo *head = acquisizione();
	printf("Benvenuto nel programma di gestione segmenti! \n");
	while(risposta != 0) {
	printf("\n *** Scegli una delle opzioni: *** \n");
	printf("1) Aggiungi un nuovo segmento alla lista \n");
	printf("2) Cancella il primo segmento della lista \n");
	printf("3) Visualizza la lista dei segmenti \n");
	printf("4) Verifica paralleli \n");
	printf("5) Verifica orizzontali \n");
	printf("0) Salva ed esci \n");
	printf("--------------------- \n \n");
	printf("-->  ");
	scanf("%d", &risposta);
	
	if(risposta == 1)
		nuovoSegmento(&head);
	else if(risposta == 2)
		cancellaSegmento(&head);
	else if(risposta == 3)
		stampaLista(head);
	else if(risposta == 4)
		verificaParalleli(head);
	else if(risposta == 5)
		verificaPerpendicolari(head);
	else if(risposta == 0) {
		printf("Grazie di aver usato il programma. \n");
		printf("Salvataggio automatico. \n");
	}
	else
		printf("Opzione non disponibile. \n");
		
	}
	
	
	salvataggio(head);

	
	
}
