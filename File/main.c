#include <stdio.h>

int main(int argc, char **argv)
{
	char stringa[100];
	
	FILE *fp = fopen("lettura", "r");
	
	if(fp == NULL)
		printf("Errore nella lettura.");
	else if (fgets(stringa, 100, fp) != NULL) {
		puts(stringa);
		fclose(fp);
	}
	else
		printf("Il file %c vuoto", 138);
}
