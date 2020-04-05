#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Punto{
	float x;
	float y;
};

struct Nodo{
	struct Punto punto;
	struct Nodo *next;
};

float distanza(struct Punto p1, struct Punto p2){
	float distanza;
	distanza = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	return distanza;
}

void distanzaMinima(struct Nodo *head){
	float dist = 0;
	
	struct Nodo *nodo1 = head;
	struct Nodo *nodo2 = head->next;
	
	/* Assegno le distanza minime ai primi due punti  come riferimento */
	struct Punto p1Min = nodo1->punto;
	struct Punto p2Min = nodo2->punto;
	float distMin = distanza(nodo1->punto, nodo2->punto);
	
	while(nodo1 != NULL){
		while(nodo2 != NULL){
			dist = distanza(nodo1->punto, nodo2->punto);
			if(dist < distMin) {
				distMin = dist;
				p1Min = nodo1->punto;
				p2Min = nodo2->punto;
			}
			nodo2 = nodo2->next;
		}
		nodo1 = nodo1->next;
	}
	
	printf("I punti a distanza minima sono: \n");
	printf("(%.2f,%.2f); (%.2f,%.2f)\n", p1Min.x, p1Min.y, p2Min.x, p2Min.y);
	printf("La loro distanza vale %.2f\n", distMin);
}

void stampaLista(struct Nodo *nodo) {
	
	printf("Ecco la lista dei punti: \n");
	while(nodo != NULL){
		printf("(%.2f,%.2f)\n", nodo->punto.x, nodo->punto.y);
		nodo = nodo->next;
	}
}


void ordinaLista(struct Nodo *head){
	struct Nodo *primo;
	struct Nodo *minimo;
	struct Nodo *nodo;
	float temp1;
	float temp2;
	
	primo = head;
	
	while(primo != NULL){
		minimo = primo;
		for(nodo = primo->next; nodo!=NULL; nodo = nodo->next){
			if((nodo->punto.x < minimo->punto.x) || ((nodo->punto.x == minimo->punto.x) && (nodo->punto.y <= minimo->punto.y)))
				minimo = nodo;
		}
		
		temp1 = primo->punto.x;
		temp2 = primo->punto.y;
		primo->punto.x = minimo->punto.x;
		primo->punto.y = minimo->punto.y;
		minimo->punto.x = temp1;
		minimo->punto.y = temp2;
		
		primo = primo->next;
	}
}

struct Nodo *leggiLista(){
	int risposta;
	struct Nodo *head;
	
	
	printf("Ciao, inserisci una lista di coordinate cartesiane: \n");
	printf("La lista ha almeno un punto? (1=SI; 0 = NO): ");
	scanf("%d%*c", &risposta);
	if(!risposta){
		printf("Arrivederci. \n");
	}
	else {
		struct Nodo *nodo = NULL;
		nodo = malloc(sizeof(struct Nodo));
		head = nodo;
		printf("Inserisci le coordinate: \n");
		printf("Ascissa: ");
		scanf("%f,", &((nodo->punto).x));
		printf("Ordinata: ");
		scanf("%f", &((nodo->punto).y));
		printf("La lista ha un altro punto (1 = SI; 0 = NO): ");
		scanf("%d%*c", &risposta);
		while(risposta) {
			nodo->next = malloc(sizeof(struct Nodo));
			nodo = nodo->next;
			printf("Inserisci le coordinate: \n");
			printf("Ascissa: ");
			scanf("%f", &((nodo->punto).x));
			printf("Ordinata: ");
			scanf("%f", &((nodo->punto).y));
			
			printf("La lista ha un altro punto (1 = SI; 0 = NO): ");
			scanf("%d%*c", &risposta);
		}
		
		
		nodo->next = NULL;
		ordinaLista(head);

		
	}
	
	return head;
}

int main(int argc, char **argv)
{
	struct Nodo *head;
	
	head = leggiLista();
	stampaLista(head);
	if(head->next != NULL)
		distanzaMinima(head);
	
	
}
