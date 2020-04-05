#include <stdio.h>
#include <stdlib.h>

struct Punto{
	float x;
	float y;
};

struct Rettangolo{
	struct Punto bs;
	struct Punto ad;
};

struct Nodo {
	struct Rettangolo r;
	struct Nodo *next;
};

float latoOrizzontale(struct Rettangolo r){
	return (r.ad.x - r.bs.x);
}

float latoVerticale(struct Rettangolo r){
	return (r.ad.y-r.bs.y);
}

float perimetro(struct Rettangolo r){
	float lo = latoOrizzontale(r);
	float lv = latoVerticale(r);
	return lo*2 + lv*2;
	
}

float area(struct Rettangolo r){
	float lo = latoOrizzontale(r);
	float lv = latoVerticale(r);
	
	return (lo*lv);
}

void isQuadrato(struct Rettangolo r){
	float lo = latoOrizzontale(r);
	float lv = latoVerticale(r);
	
	if (lo == lv)
		printf("Il rettangolo %c un quadrato. \n", 138);
	else
		printf("Non %c un quadrato. \n", 138);
}

void inserisciRettangolo(struct Nodo **head){
	struct Nodo *nodo = NULL;
	nodo = malloc(sizeof(struct Nodo));
	float lo, lv;
	
	printf("Inserisci le coordinate del vertice in basso a sinistra: \n");
	printf("Ascissa: ");
	scanf("%f", &(nodo->r.bs.x));
	printf("Ordinata: ");
	scanf("%f,", &(nodo->r.bs.y));
	printf("Inserisci la lunghezza del lato orizzontale: ");
	scanf("%f", &lo);
	printf("Inserisci la lunghezza del lato verticale: ");
	scanf("%f,", &lv);
	
	nodo->r.ad.x = (nodo->r.bs.x) + lo;
	nodo->r.ad.y = (nodo->r.bs.y) + lv;
	
	// Collego il nuovo primo nodo a head (che ora è il secondo)
	nodo->next = *head;
	*head = nodo; //Nuova testa 
	
}

void cancellaUltimo(struct Nodo **head){
	struct Nodo *nodoPrec;
	struct Nodo *nodoCorr;
	
	
	// Nessun elemento nella lista?
	if(*head == NULL)
		printf("Nessun rettangolo da cancellare.\n");
	else if((*head)->next == NULL){
		free(*head);
		*head = NULL;
	}
	else {
		nodoPrec = *head;
		nodoCorr = (*head)->next;
		while(nodoCorr->next != NULL){
			nodoPrec = nodoCorr;
			nodoCorr = nodoCorr->next;
		}
		
		nodoPrec->next = NULL;
		free(nodoCorr);
	}
}

void stampaLista(struct Nodo *nodo){
	struct Punto p1;
	struct Punto p2;
	
	
	if(nodo == NULL)
		printf("Nessun rettangolo inserito. \n");
	else {
		printf("** LISTA RETTANGOLI: ** \n");
		while(nodo != NULL){
			
			// STAMPA VERTICI
			printf("- VERTICI: \n");
			printf("Punto in basso a sinistra: (%.2f,%.2f) \n", nodo->r.bs.x, nodo->r.bs.y);
			// Calcolo le coordinate del punto in alto a sinistra
			p1.x = nodo->r.bs.x;
			p1.y = nodo->r.ad.y;
			printf("Punto in alto a sinistra: (%.2f,%.2f) \n", p1.x, p1.y);
			printf("Punto in alto a destra: (%.2f,%.2f) \n", nodo->r.ad.x, nodo->r.ad.y);
			// Calcolo le coordinate del punto in basso a destra
			p2.x = nodo->r.ad.x;
			p2.y = nodo->r.bs.y;
			printf("Punto in basso a destra: (%.2f,%.2f) \n", p2.x, p2.y);
			
			// STAMPA CARATTERISTICHE
			printf("- PERIMETRO: %.2f \n", perimetro(nodo->r));
			printf("- AREA: %.2f \n", area(nodo->r));
			isQuadrato(nodo->r);
		
			printf("------ \n");
			
			// Passa al nodo sucerssivo
			nodo = nodo->next;
		}
	}
}

struct Nodo *acquisizione() {
	FILE *fpIN = fopen("rettangoli.dat", "rb");
	struct Nodo *head = NULL;
	struct Nodo *current;
	struct Nodo *previous;
	
	struct Rettangolo rettangolo;
	int letto;
	
	// Se non hai aperto il file (= null) non devi fare nulla
	if(fpIN != NULL) {
		// Leggi il primo nodo della lista
		letto = fread(&rettangolo, sizeof(struct Rettangolo), 1, fpIN);
		if(letto){ // almeno un rettangolo è presente nel file
			/* Memorizza nell'heap il primo nodo della lista */
			head = malloc(sizeof(struct Nodo));
			head->r = rettangolo;
			
			/* Devi tenere traccia dell'ultimo nodo letto, per collegarlo al successivo nella lista */
			previous = head;
			/* Adesso leggi gli altri nodi */
			do{
				letto = fread(&rettangolo, sizeof(struct Rettangolo), 1, fpIN);
				if(letto) {
					current = malloc(sizeof(struct Nodo));
					current->r = rettangolo;
					
					/* Collegato il nuovo nodo al precedente */
					previous->next = current;
					
					/* il nuovo nodo diventa il precedente */
					previous = current;
				}
				else 
					previous->next = NULL;
			}
			while(letto);
		}
	}
	
	return head;
}


void salvataggio(struct Nodo *nodo){
	FILE *fpOUT = fopen("rettangoli.dat", "wb");
		while(nodo!= NULL){
			fwrite(&(nodo->r), sizeof(struct Rettangolo), 1, fpOUT);
			nodo = nodo->next;
		}
		fclose(fpOUT);
		printf("Salvataggio automatico effettuato. \n");
}




int main(int argc, char **argv)
{
	struct Nodo *head = acquisizione();
	
	int risposta = -1;
	
	printf("Ciao, benvenuto nel programma rettangoli.\n");
	while(risposta != 0){
		printf("Scegli un'opzione: \n");
		printf("1) Inserisci un rettangolo in testa alla lista \n");
		printf("2) Cancella l'ultimo rettangolo della lista \n");
		printf("3) Visualizza la lista corrente di rettangoli (e delle loro specifiche) \n");
		printf("4) Calcola l'intersezione fra due rettangoli a scelta \n");
		printf("0) Per uscire dal programma \n");
		printf("------------------------------- \n");
		printf("-----> ");
		scanf("%d", &risposta);
	
	
	if (risposta == 1)
		inserisciRettangolo(&head);
		
	if(risposta == 2)
		cancellaUltimo(&head);
	
	if (risposta == 3)
		stampaLista(head);
	
	}
	
	
	salvataggio(head);
	
}
