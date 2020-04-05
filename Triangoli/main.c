#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Punto {
	float x;
	float y;
};

struct Triangolo {
	struct Punto V1;
	struct Punto V2;
	struct Punto V3;
};

struct Nodo {
	struct Triangolo t;
	struct Nodo *next;
};

/***************************
 *** FUNZIONI GEOMETRICHE ****
 *****************************/

float distanza(struct Punto V1, struct Punto V2) {
	return sqrt((V1.x - V2.x)*(V1.x - V2.x) + (V1.y - V2.y)*(V1.y - V2.y));
}

float perimetro(struct Triangolo t) {
	float latoA = distanza(t.V1, t.V2);
	float latoB = distanza(t.V1, t.V3);
	float latoC = distanza(t.V2, t.V3);
	return latoA+latoB+latoC; 
}

float area(struct Triangolo t) {
	float latoA = distanza(t.V1, t.V2);
	float latoB = distanza(t.V1, t.V3);
	float latoC = distanza(t.V2, t.V3);
	float semiPerimetro = perimetro(t) / 2;
	return sqrt(semiPerimetro * (semiPerimetro-latoA) * (semiPerimetro-latoB) * (semiPerimetro-latoC));
}

/**********************************
 ********** STAMPE ***************
 ********************************/
 
 void stampaTriangolo(struct Triangolo t) {
	 printf("Vertice A: (%.2f,%.2f) \n", t.V1.x, t.V1.y);
	 printf("Vertice B: (%.2f,%.2f) \n", t.V2.x, t.V2.y);
	 printf("Vertice C: (%.2f,%.2f) \n", t.V3.x, t.V3.y);
	 printf("Perimetro: %.2f \n", perimetro(t));
	 printf("Area: %.2f \n", area(t));
	 
}
 
 
 void stampaLista(struct Nodo *lista) {
	 if(lista != NULL) {
		 printf("*** LISTA TRIANGOLI: *** \n");
		 while(lista != NULL) {
			 stampaTriangolo(lista->t);
			 lista = lista->next;
		 }
	 }
	 else {
		 printf("Non ci sono triangoli nella lista. \n");
	 }
 }
 
 
/********************************
 ******* ALLINEAMENTO PUNTI *****
 ***********************************/
 
int collineari(struct Punto V1, struct Punto V2, struct Punto V3) {
	return !((V1.x-V2.x)/(V1.y-V2.y) == (V3.x-V2.x)/(V3.y-V2.y));
}

/******************************
 ********* ORDINAMENTO ********
 ******************************/
 
void ordinamento(struct Nodo *head) {
	struct Nodo *primo;
	struct Nodo *minimo;
	struct Nodo *nodo;
	struct Triangolo temp;
	
	if(head != NULL) {
		primo = head; // PRIMO ELEMENTO DA ORDINARE
		while(primo != NULL) {
			minimo = primo; 
			for(nodo = primo->next; nodo!=NULL; nodo = nodo->next) {
				/* minore del minimo? */
				if(area(nodo->t) < area(minimo->t))
					minimo = nodo;
			}
			
			temp = primo->t;
			primo->t = minimo->t;
			minimo->t = temp;
			
			/* Fai scorrre il primo elemento non ordinato */
			primo = primo->next;
		}
	}
	else
		printf("Non ci sono triangoli da ordinare. \n");
	
}
 

/******************************
 ******** INSERIMENTO **********
 ******************************/
 
void inserisci(struct Nodo **head, struct Triangolo triangolo) {
	struct Nodo *nuovoNodo = NULL;
	nuovoNodo = malloc(sizeof(struct Nodo));
	
	nuovoNodo->t = triangolo;
	nuovoNodo->next = *head;
	*head = nuovoNodo;
} 

 
void nuovoTriangolo(struct Nodo **head) {
	struct Triangolo t;
	
	printf("Inserisci i tre vertici del triangolo: \n");
	
	printf("Vertice 1: \n");
	printf("Ascissa: ");
	scanf("%f", &t.V1.x);
	printf("Ordinata: ");
	scanf("%f", &(t.V1.y));
	
	printf("Vertice 2: \n");
	printf("Ascissa: ");
	scanf("%f", &(t.V2.x));
	printf("Ordinata: ");
	scanf("%f", &(t.V2.y));
	
	printf("Vertice 3: \n");
	printf("Ascissa: ");
	scanf("%f", &(t.V3.x));
	printf("Ordinata: ");
	scanf("%f", &(t.V3.y));
	
	if(collineari(t.V1, t.V2, t.V3))
		inserisci(head, t);
	else
		printf("I punti non formano un triangolo. \n");
}
	
/******************************
 ******** CANCELLAMENTO ********
 *****************************/
void cancellaTriangolo(struct Nodo **head) {
	struct Nodo *nodo;
	
	if(*head != NULL) {
		nodo = (*head)->next;
		free(*head);
		*head = nodo;
		printf("Il primo triangolo %c stato cancellato. \n", 138);
	}
	else
		printf("Nessun triangolo da cancellare. \n");
}

/**********************************
 ******** GESTIONE FILE *********
 ********************************/
 
struct Nodo *acquisizione() {
	struct Nodo *head = NULL;
	struct Nodo *nodoCurr;
	struct Nodo *nodoPrec;
	struct Triangolo triangolo;
	int letto = 0; 
	
	FILE *fpIN = fopen("triangoli.dat", "rb");
	if(fpIN != NULL) {
		letto = fread(&triangolo, sizeof(struct Triangolo), 1, fpIN);
		if(letto){
			head = malloc(sizeof(struct Nodo));
			head->t = triangolo;
			
			nodoPrec = head;
			
			do {
				letto = fread(&triangolo, sizeof(struct Triangolo), 1, fpIN);
				if(letto){
					nodoCurr = malloc(sizeof(struct Nodo));
					nodoCurr->t = triangolo;
					
					nodoPrec->next = nodoCurr;
					nodoPrec = nodoCurr;
				}
				else {
					nodoPrec->next = NULL;
				}
			}
			while(letto);
		}
	}
	
	fclose(fpIN);
	
	return head;
	
} 

void salvataggio(struct Nodo *nodo) {
	FILE *fpOUT = fopen("triangoli.dat", "wb");
	while(nodo != NULL) {
		fwrite(&nodo->t, sizeof(struct Triangolo), 1, fpOUT);
		nodo = nodo->next;
	}
	
	fclose(fpOUT);
	printf("Salvataggio automatico effettuato. \n");
}

int main(int argc, char **argv)
{
	struct Nodo *head = acquisizione();
	printf("Benvenuto nel programma Triangoli! \n");
	int risposta = -1;
	
	while(risposta != 0) {
		printf("\n Scegli un'opzione: \n");
		printf("1) Inserisci un triangolo in testa alla lista \n");
		printf("2) Cancella il primo triangolo della lista \n");
		printf("3) Visualizza la lista dei triangoli e le loro specifiche \n");
		printf("4) Ordina la lista in base all'area \n");
		scanf("%d", &risposta);
		
		if(risposta == 1)
			nuovoTriangolo(&head);
		else if(risposta == 2)
			cancellaTriangolo(&head);
		else if(risposta == 3)
			stampaLista(head);
		else if(risposta == 4)
			ordinamento(head);
	}
	
	
	salvataggio(head);
}
