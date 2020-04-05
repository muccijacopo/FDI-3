#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int risposta = 0;
	char articolo[50];
	int numero;
	
	printf("- Benvenuto in questo programma di gestione della spesa. - \n \n");
	printf("Creare una nuova lista della spesa? (1 = SI; 0 = NO): ");
	scanf("%d%*c", &risposta);
	if (risposta) {
		FILE *fp = fopen("Lista della spesa", "w");
		while(risposta) {
		
			printf("Articolo: ");
			fgets(articolo, 50, stdin);
			articolo[strlen(articolo)-1] = '\0';
			fprintf(fp, "%s  ", articolo);
			printf("Quanti te ne servono? ");
			scanf("%d%*c", &numero);
			fprintf(fp, "%d\n", numero);
	
			// Continua?
			printf("Altro articolo? (1 = SI; 0 = NO): ");
			scanf("%d%*c", &risposta);
		}
		fclose(fp);
		printf("Lista salvata. \n");
	}
	else
		printf("Grazie alla prossima!");
	
	printf("Visualizzare lista della spesa? (1 = SI; 0 = NO): ");
	scanf("%d%*c", &risposta);
	if(risposta) {
		FILE *fp = fopen("Lista della spesa", "r");
		fgets( )
	}
}
