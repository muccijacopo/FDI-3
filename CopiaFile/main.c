#include <stdio.h>
#include <string.h>

void copiaFile(FILE *fpIN, FILE *fpOUT) {
	char carattere;
	carattere = fgetc(fpIN);
	while(carattere != EOF) {
		fputc(carattere, fpOUT);
		carattere = fgetc(fpIN);
	}
	
	printf("File copiato");
}


int main(int argc, char **argv)
{
	FILE *fpIN;
	FILE *fpOUT;
	char copiato[50];
	char copia[50];
	
	printf("Quale file vuoi copiare? ");
	scanf("%s", copiato);
	printf("Quale nome vuoi dare al nuovo file copia? ");
	scanf("%s", copia);
	
	fpIN = fopen(copiato, "r");
	if(fpIN == NULL)
		printf("Il file %s non esiste, quindi non puoi copiarlo.", copiato);
	else {
		fpOUT = fopen(copia, "w"); //Creazione del file copia
		copiaFile(fpIN, fpOUT);
		fclose(fpIN);
		fclose(fpOUT);
	}
}
