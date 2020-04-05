#include <stdio.h>
#include <stdlib.h>

struct Razionale {
	int numeratore;
	int denominatore;
};

struct Retta {
	int verticale;
	struct Razionale coefficiente;
	struct Razionale intercetta;
};


struct Nodo {
	struct Retta retta;
	struct Nodo *next;
};

/* Verifica se una retta precede un'altra retta */
int precede(struct Retta r1, struct Retta r2){
	int vero;
	
	/* Se la seconda è verticale allora sì */
	if(r2.verticale)
		vero = 1; 
	else 
		if(r1.verticale)
			vero = 0;
		else
			/* Confronta i coefficienti */
			vero = ((float)r1.coefficiente.numeratore)/((float)r1.coefficiente.denominatore) <= ((float)r2.coefficiente.numeratore)/((float)r2.coefficiente.denominatore);
			
	return vero;
}

void inserisci(struct Nodo **head, struct Retta r){
	/* Alloca memoria per il nuovo nodo */
	struct Nodo *nodo = malloc(sizeof(struct Nodo));
	// Riempo il campo dati
	nodo->retta = r;
	
	/* Ora devi cercare il posto giusto per l'inserimento */
	
	// Se la lista è vuota puoi inserirlo subito
	if(*head == NULL) {
		nodo->next = NULL;
		*head = nodo; //Nuova testa
		
	}
	else {
		/* Il nuovo elemento diventa il primo? */
		if(precede(r, (*head)->retta)) {
			nodo->next = *head;
			*head = nodo; 
		}
		else {
			/* Il nuovo elemento non diventa il primo */
			struct Nodo *nodoPrec = *head;
			struct Nodo *nodoCurr = nodoPrec->next;
			/* Cicla fino a quando nodoPrec e nodoCurr sono i due elementi fra i quali inserire nodo */
			int trovato = 0;
			while(nodoCurr != NULL && !trovato){
				if(precede(r, nodoCurr->retta)){
					trovato = 1;
				}
				else {
					nodoPrec = nodoCurr;
					nodoCurr = nodoCurr->next;
				}
			}
			/*Inserisci fra nodoPrec e nodoCurr */
			nodoPrec->next = nodo;
			nodo->next = nodoCurr; //può essere NULL
		}
	}
}

void nuovaRetta(struct Nodo **head){
	// Precondizioni: denominatore != 0
	struct Retta r;
	
	printf("La nuova retta %c verticale? (1 = SI, 0 = NO): ", 138);
	scanf("%d", &r.verticale);
	if(r.verticale){
		// Fai inserire il numeratore e il denominatore dell'intercetta
		printf("Inserisci il numeratore dell'intercetta con l'asse x: ");
		scanf("%d", &r.intercetta.numeratore);
			do{
				printf("Inserisci il denominatore dell'intercetta con l'asse x: ");
				scanf("%d", &r.intercetta.denominatore);
			} 
			while(r.intercetta.denominatore == 0);
	}
	else {
		//Fai inserire numeratore e denominatore del coefficiente angolare 
		printf("Inserisci il numeratore del coefficiente angolare: ");
		scanf("%d", &r.coefficiente.numeratore);
		printf("Inserisci il denominatore del coefficiente angolare: ");
		scanf("%d", &r.coefficiente.denominatore);
		// Fai inserire il numeratore e il denominatore dell'intercetta
		printf("Inserisci il numeratore dell'intercetta: ");
		scanf("%d", &r.intercetta.numeratore);
		printf("Inserisci il denominatore dell'intercetta");
		scanf("%d", &r.intercetta.denominatore);
		
	}
	
	inserisci(head, r);
	printf("Retta inserita nella lista e ordinata!\n");
}

void stampaRetta(struct Retta r) {

	if(r.verticale == 1) { // NO Y
		printf("L'equazione della retta %c x =", 138);
		if(r.intercetta.numeratore == 0)
			printf(" 0\n");
		else
			if((r.intercetta.numeratore > 0 && r.intercetta.denominatore < 0) || (r.intercetta.numeratore < 0 && r.intercetta.denominatore > 0))
				printf(" -");
			if(r.intercetta.numeratore < 0)
				r.intercetta.numeratore = -r.intercetta.numeratore;
			printf(" %d", r.intercetta.numeratore);
			
			if(r.intercetta.denominatore < 0)
				r.intercetta.denominatore = -r.intercetta.denominatore;
			if(r.intercetta.denominatore != 1)
				printf("/%d\n", r.intercetta.denominatore);
			else
				printf("\n");
	}
	else { 
		printf("L'equazione della retta %c y =", 138);
		/* stampa il termine mx */
		if(r.coefficiente.numeratore != 0) {//il termine c'è
			if((r.coefficiente.numeratore > 0 && r.coefficiente.denominatore < 0) || (r.coefficiente.numeratore < 0 && r.coefficiente.denominatore > 0))
				printf(" -");
				
			if(r.coefficiente.numeratore < 0)
				r.coefficiente.numeratore = -r.coefficiente.numeratore;
			printf(" %d", r.coefficiente.numeratore);
			if(r.coefficiente.denominatore < 0)
				r.coefficiente.denominatore = -r.coefficiente.denominatore;
			if(r.coefficiente.denominatore != 1)
				printf("/%d", r.coefficiente.denominatore);
		}
		
		if(r.intercetta.numeratore == 0)
			if(r.coefficiente.numeratore == 0)
				printf(" 0\n");
			else
				printf(" \n");
		else {
			if((r.intercetta.numeratore > 0 && r.intercetta.denominatore < 0) || (r.intercetta.numeratore < 0 && r.intercetta.denominatore > 0))
				printf(" -");
			else {
				if(r.coefficiente.numeratore!=0)
					printf(" +");
			}
			
			if(r.intercetta.numeratore < 0)
				r.intercetta.numeratore = -r.intercetta.numeratore;
			printf(" %d", r.intercetta.numeratore);
			if(r.intercetta.denominatore < 0)
				r.intercetta.denominatore = -r.intercetta.denominatore;
			if(r.intercetta.denominatore != 1)
				printf("/%d\n", r.intercetta.denominatore);
			else
				printf("\n");
		}
	}
		
}

void stampaLista(struct Nodo *lista) {
	if(lista == NULL)
		printf("La lista %c vuota, niente da stampare. \n", 138);
	else {
		printf("LISTA RETTE: \n");
		while(lista != NULL) {
			stampaRetta(lista->retta);
			lista = lista->next;
		}
		printf("\n");
	}
}

/******************************************
 ********** CANCELLAZIONE *************
 ****************************************/

void eliminaRetta(struct Nodo **head){
	struct Nodo *nodo; // Nuovo primo nodo
	
	if(*head == NULL)
		printf("Nessuna retta da cancellare. \n");
	else {
		nodo = (*head)->next;
		free(*head); // Dealloca la memoria del primo nodo
		*head = nodo;
		printf("La prima retta della lista %c stata cancellata. \n", 138);
	}
}


/**********************************
 ******** GESTIONE FILE **********
 *********************************/
 
struct Nodo *acquisizione() {
	FILE *fpIN = fopen("rette.dat", "rb");
	struct Nodo *head = NULL;
	struct Nodo *current;
	struct Nodo *previous;
	struct Retta retta;
	int letto;
	
	/* Verifico se ho aperto il file (se non esiste non viene aperto nulla!!!) */
	if(fpIN != NULL) {
		// Leggi il primo nood della lista
		letto = fread(&retta, sizeof(struct Retta), 1, fpIN);
		if(letto) {
			head = malloc(sizeof(struct Nodo));
			head->retta = retta;
			
			previous = head;
			// Adesso leggi tutti gli altri nodi, se ci sono
			do {
				letto = fread(&retta, sizeof(struct Retta), 1, fpIN);
				if(letto) {
					current = malloc(sizeof(struct Nodo));
					current->retta = retta;
					
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
	
	return head;
	
} 
 
 
 
void salvataggio(struct Nodo *lista) {
	 FILE *fpOUT = fopen("rette.dat", "wb");
	 while(lista != NULL) {
		 fwrite(&(lista->retta), sizeof(struct Retta), 1, fpOUT);
		 lista = lista->next;
	 }
}


/***********************************
 *******FUNZIONE PRINCIPALE *******
 *********************************/

int main(int argc, char **argv)
{
	int risposta = -1;
	struct Nodo *head = acquisizione();
	printf("Benvenuto nel programma Rette! \n");
	
	while(risposta != 0){
		printf("\n*****MENU DI SCELTA******* \n");
		printf("Scegli un'opzione tra le seguenti: \n");
		
		printf("1) Aggiungi una retta in testa alla lista \n");
		printf("2) Cancella la retta in testa alla lista \n");
		printf("3) Visualizza l'elenco delle rette \n");
		printf("0) Per uscire dal programma e salvare. \n");
		printf("------------------------------------ \n");
		printf("Scelta ---> ");
		scanf("%d", &risposta);
	
	
		if(risposta == 1)
			nuovaRetta(&head);
		else if(risposta == 2)
			eliminaRetta(&head);
		else if(risposta == 3)
			stampaLista(head);
	}
	
	printf("Vuoi salvare le lista corrente? (1 = SI, 0 = NO): ");
	scanf("%d", &risposta);
	if(risposta)
		salvataggio(head);
		
}
