#include "functionsClient.h"
#include "../protocol/protocoloCMD.h"

/*
FUNCION
Descipcion :
Nombre :
Recibe:
Retorna:
*/

void showHelpClient()
	{
  system("clear");
  printf("----------------------------------------------------------------------\n");
  printf("--------------------------CMD----------------------------\n");
  printf("----------------------------------------------------------------------\n");
  printf("\n");
  printf("Puede realizar las siguientes operaciones ejecutando los comandos:\n\n");
  printf("<ls|pwd|cd> <dir>:\n\n");
  printf("HELP Ayuda\n");
  printf("SALIR - Sale del programa\n");
  printf("\n");
}

void showReadComando(char *teclado)
{
			
	printf( "$ > ");
	fgets(teclado, 255, stdin);
	teclado[strlen(teclado) - 1] = '\0';
	fflush(stdin);
	
}


