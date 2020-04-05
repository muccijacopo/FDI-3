#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DEFINIZIONE STRUTTURE */
#define DIMENSIONE 31

/* STRUTTURE DATI */

struct Data {
	int giorno;
	int mese;
	int anno;
};

struct Indirizzo {
	char via[50];
	int civico;
	char citta[30];
};

struct Persona {
	char nome[30];
	char cognome[30];
	struct Data dataDiNascita;
	struct Indirizzo indirizzo;
};

/* VARIABILI GLOBALI */
struct Persona anagrafe[DIMENSIONE];
int numeroPersone;

/* FUNZIONI AUSILIARE */

void inserisciData(struct Data *data) {
	printf("Giorno: ");
	scanf("%d", &(data->giorno));
	printf("Mese: ");
	scanf("%d", &(data->mese));
	printf("Anno: ");
	scanf("%d%*c", &(data->anno));
}

void inserisciIndirizzo(struct Indirizzo *indirizzo) {
	printf("Via: ");
	fgets(indirizzo->via, 50, stdin);
	(indirizzo->via)[strlen(indirizzo->via)-1] = '\0';
	printf("Civico: ");
	scanf("%d%*c", &(indirizzo->civico));
	printf("Citt%c: ", 133);
	fgets(indirizzo->citta, 50, stdin);
	(indirizzo->citta)[strlen(indirizzo->citta)-1] = '\0';
}

void stampaData(struct Data *data) {
	printf("DATA DI NASCITA: %d/%d/%d\n", data->giorno, data->mese, data->anno);
}

void stampaIndirizzo(struct Indirizzo *indirizzo) {
	printf("INDIRIZZO: %s %d %s \n", indirizzo->via, indirizzo->civico, indirizzo->citta);
}

//Output persona
void stampaPersona(struct Persona *persona) {
	printf("Nome: %s\n", persona->nome);
	printf("Cognome: %s\n", persona->cognome);
	stampaData(&(persona->dataDiNascita));
	stampaIndirizzo(&(persona->indirizzo));
	printf("----- \n");

}

void sposta(struct Persona *persona) {
	strcpy((persona-1)->nome, persona->nome);
	strcpy((persona-1)->cognome, persona->cognome);
	persona->dataDiNascita = (persona-1)->dataDiNascita;
	persona->indirizzo = (persona-1)->indirizzo;
}


/* FUNZIONI PRINCIPALI */

void inserisciPersona(struct Persona *persona) {
	printf("Inserisci il nome: ");
	fgets(persona->nome, DIMENSIONE, stdin);
	(persona->nome)[strlen(persona->nome)-1] = '\0';
	
	printf("Inserisci il cognome: ");
	fgets(persona->cognome, DIMENSIONE, stdin);
	(persona->cognome)[strlen(persona->cognome)-1] = '\0';
	
	printf("Inserisci la data di nascita: \n");
	inserisciData(&(persona->dataDiNascita));
	
	printf("Inserisci l'indirizzo: \n");
	inserisciIndirizzo(&(persona->indirizzo));
}

struct Persona *ricercaPersona() {
	char nome[30];
	char cognome[30];
	
	printf("Nome: ");
	fgets(nome, 30, stdin);
	nome[strlen(nome)-1] = '\0';
	printf("Cognome: ");
	fgets(cognome, 30, stdin);
	cognome[strlen(cognome)-1] = '\0';
	
	struct Persona *persona = NULL; //persona da trovare
	
	int i = 0;
	while(i < numeroPersone && persona == NULL) {
		if(strcmp(nome, (anagrafe+i)->nome) == 0 && strcmp(cognome, (anagrafe+i)->cognome) == 0)
				persona = anagrafe + i;
		else
				i++;
	}
	
	return persona;
	
}

struct Persona *cancellaPersona() {
	struct Persona *persona; //la persona da cancellare
	
	persona = ricercaPersona();
	
	// se esiste cancellala
	if(persona != NULL) {
		int i = 0;
		/* anagrafe+dimensione-1 è l'indirizzo dell'ultimo elemento */
		while(persona+i+1 <= anagrafe+numeroPersone-1) {
			sposta(persona+i+1);
			i++;
		}
		
		
	}
	
	return persona;
}

void visualizzaAnagrafe() {
	printf("\n ************** \n");
	printf(" ARCHIVIO ANAGRAFE \n");
	printf("\n ************** \n");
	printf("Persone registrate: %d \n", numeroPersone);
	printf("----- \n");
	// Visualiza tutte le persone nell'archivio
	for(int i=0; i<numeroPersone; i++){
		stampaPersona(anagrafe+i);
	}
}

void copiaBackup(){
	FILE *backup, *dat;
	dat = fopen("anagrafe.dat", "r");
	backup = fopen("anagrafe.bak", "w");
	int c = fgetc(dat);
	while(c != EOF) {
		fputc(c, backup);
		c = fgetc(dat);
	}
	fclose(backup);
	fclose(dat);
	
	return;
}

void acquisisciFile(){
	int i;
	char *fineFile;
	
	FILE *fpIN;
	char buf[10];
	fpIN = fopen("anagrafe.dat", "r");
	
	if(fpIN == NULL){
		printf("Non sono presenti persone nell'archivio.\n");
		numeroPersone = 0;
	}
	else {
		i = 0;
		do {
			fscanf(fpIN, "%s%s", anagrafe[i].nome, anagrafe[i].cognome);
			fscanf(fpIN, "%d%d%d", &(anagrafe[i].dataDiNascita.giorno), &(anagrafe[i].dataDiNascita.mese), &(anagrafe[i].dataDiNascita.anno));
			fscanf(fpIN, "%s%d%s", anagrafe[i].indirizzo.via, &(anagrafe[i].indirizzo.civico), anagrafe[i].indirizzo.citta);
			fineFile = fgets(buf, 10, fpIN);
			i++;
		}
		while(fineFile != NULL);
		numeroPersone = i;
	}
	
	fclose(fpIN);
	copiaBackup();
}


void salvaAnagrafe(){
	FILE *fpOUT;
	
	fpOUT = fopen("anagrafe.dat", "w");
	if(fpOUT != NULL){
		for(int i=0; i<numeroPersone; i++){
			fprintf(fpOUT, "%s\n", anagrafe[i].nome);
			fprintf(fpOUT, "%s\n", anagrafe[i].cognome);
			fprintf(fpOUT, "%d\n", anagrafe[i].dataDiNascita.giorno);
			fprintf(fpOUT, "%d\n", anagrafe[i].dataDiNascita.mese);
			fprintf(fpOUT, "%d\n", anagrafe[i].dataDiNascita.anno);
			fprintf(fpOUT, "%s\n", anagrafe[i].indirizzo.via);
			fprintf(fpOUT, "%d\n", anagrafe[i].indirizzo.civico);
			fprintf(fpOUT, "%s", anagrafe[i].indirizzo.citta);
			if(i != numeroPersone-1)
				fprintf(fpOUT, "\n");
		}
		fclose(fpOUT);
	}
}

int main(int argc, char **argv)
{
	int risposta = -1;
	
	printf("|| GESTIONE DATI ANAGRAFE || \n\n");
	
	acquisisciFile();
	visualizzaAnagrafe();
	
	
	// Menu di scelta
	while(risposta != 0) {
		printf("\n \n");
		printf("Puoi svolgere le seguenti operazioni:\n");
		printf("Introduci 1 -> Inserisci una persona\n");
		printf("Introduci 2 -> Cancella una persona\n");
		printf("Introduci 3 -> Cerca una persona\n");
		printf("Introduci 4 -> Visualizza archivio\n");
		printf("Introduci 0 -> Chiudi il programma\n");
		printf("--> ");
		scanf("%d%*c", &risposta);
	
		// Inserimento persona
		if (risposta == 1) {
			if(numeroPersone < DIMENSIONE) {
				inserisciPersona(anagrafe+numeroPersone);
				numeroPersone++;
				printf("Persona aggiunta con successo. \n");
			}
			else
				printf("Capienza massima.\n");
		}
		else if(risposta == 2) {
			if(cancellaPersona()){
				numeroPersone--;
				printf("Persona cancellata correttamente. \n");
			}
			else
				printf("Mi dispiace, la persona non %c presente nell'archivio\n", 138);
		}
		else if(risposta == 3) {
			struct Persona *persona = ricercaPersona();
			if(persona != NULL) {
				printf("\nEcco la persona cercata \n");
				stampaPersona(persona);
			}
			else
				printf("Mi dispiace, la persona non %c presente nell'archivio", 138);
		}	
		// Visualizza tutto l'archivio
		else if(risposta == 4)
			visualizzaAnagrafe();
			
		else if(risposta != 0)
			printf("Non %c un'opzione. Riprova con una scelta dal menu.\n", 138);
	}
	
	salvaAnagrafe();
		
	
}
