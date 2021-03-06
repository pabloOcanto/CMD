/*Fecha de ultima modificacion 26/04/2016*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <pthread.h>
#include "functionsClient.h"
#include "../protocol/protocoloCMD.h"

int signalClose;

void close_signal ( int signal)
{
	printf("Se ha precionado Ctrl-c \n");
	signalClose=1;
	exit(signal);
}


int main(int argc, char *argv[]) {

	//Signal para cerrar la app
	signal(SIGINT, close_signal);
	signalClose=0;

	int n = 1;
	int sd;
	int lon;

	//char buffer[P_SIZE];
	struct sockaddr_in servidor;
	struct sockaddr_in cliente;
	struct hostent *h;
	char *datos = NULL;

	

	if (argc < 2) {
		//printf("Debe ejecutar %s (nombre de host)\n",argv[0]);
		printf("Debe ejecutar la direccion de ip");
		exit (-1);
	}

	sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(4444);
	//servidor.sin_addr.s_addr = inet_addr("x.x.x.x");

	if ( h = gethostbyname ( argv [1] ) ) {
		memcpy(&servidor.sin_addr, h->h_addr, h->h_length);
	}

	lon = sizeof(servidor);

	if (connect (sd, (struct sockaddr *) &servidor, lon) < 0) {

		perror ("Error en connect");
		exit(-1);
	}
	
	enviar_mensaje(sd,SOLICITUD_SIGN_IN,"Server me quiero conectar"); 
	
	while ((n!=0)) {

		protocoloCMD *mjs;
		mjs = (protocoloCMD*) malloc(sizeof(protocoloCMD));
		n = leer_mensaje(sd, mjs);

		if( n > 0)
		{
			switch (mjs->header.codigo)
			{
				case ACK_SIGN_IN:
					{
						
						#ifdef DEBUG					      
  						printf("Server say: %s\n", mjs->body.mensage);
						#endif
						char loggin[80];	
						  system("clear");
  						  printf("---------------------------------------------------------------\n");
  						  printf("--------------------------LOGUIN CMD-----------------------------\n");
  						  printf("---\n");

						  printf("-------------------------USER,PASSWORD-------------------------\n");			
						  fgets(loggin,80,stdin);	

							
						enviar_mensaje(sd,LOGGIN_USER,loggin);
						//printf("--------------------------------\n");

						
						break;
					}
				case USER_VALID :{

						printf("Server say: %s\n", mjs->body.mensage);
						showHelpClient();						
						char res[255];
						showReadComando(res);
					        char *std = (char *) malloc (sizeof(char) *255);
						strcpy(std,res);
						printf("Enviando comando -%s",std);
						enviar_mensaje(sd,SOLICITUD_COMANDO,std);
						
						
						break;
				}
				case RESPUESTA_COMANDO:{

						printf("%s",mjs->body.mensage);
						char res[255];
						showReadComando(res);
					        char *std = res;
						if(strcmp(res,"SALIR")==0)
						{
							enviar_mensaje(sd,EXIT_COMANDO,std);
							n = 0;
						}
						else {
							enviar_mensaje(sd,SOLICITUD_COMANDO,std);
						     }
							
						break;	
				}

				case USER_ERROR :{

						#ifdef DEBUG					      
  						printf("Server say: %s\n", mjs->body.mensage);
						#endif
						char loggin[80];	
						  system("clear");
  						  printf("----------------------------Datos Invalidos--------------------------------\n");
  						  printf("--------------------------LOGUIN CMD-----------------------------\n");
  						  printf("---\n");

						  printf("-------------------------USER,PASSWORD-------------------------\n");			
						  fgets(loggin,80,stdin);	

							
						enviar_mensaje(sd,LOGGIN_USER,loggin);
						//printf("--------------------------------\n");

						break;
				}
				
				default:
					break;
				}
			}
		else
			{
				n = 0;
			}

		free(mjs);


	}
	printf("Se ah desconectado del servidor.\n");

	close(sd);

	return(0);
}
