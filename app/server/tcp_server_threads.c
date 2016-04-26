#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include "../protocol/protocoloCMD.h"
#include "funciones.h"
#define DEBUG


// COMPILAR: gcc -o ./build/server tcp_server_threads.c protocoloCMD.c -l pthread 


void *cliente (void *);

int clients;

int main(int argc, char *argv[]) {

	
	int lon;
	int sd;
	int sd_cli;
	struct sockaddr_in sock_servidor;
	struct sockaddr_in sock_cliente;
	pthread_t tid;
	
	sock_servidor.sin_family = AF_INET;
	sock_servidor.sin_port = htons (4444);
	sock_servidor.sin_addr.s_addr = INADDR_ANY;

	sd = socket (PF_INET, SOCK_STREAM, 0);

	 int  yes = 1;			//char yes='1'; // use this under Solaris 
  	if ( setsockopt ( sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof ( int ) ) ==-1 ) {
 	  perror ( "setsockopt" );
  	  exit ( 1 );
  	}
	if ( bind ( sd , (struct sockaddr *) &sock_servidor , sizeof(sock_servidor) ) < 0 ) {
		perror("Error en bind");
		exit (-1);
		}

	
	listen ( sd , 5);

	
	printf("Server Iniciado\n");
	
	while (1) {

		lon = sizeof(sock_cliente);

		sd_cli = accept ( sd , (struct sockaddr *) &sock_cliente , &lon);

		pthread_create ( &tid, NULL, cliente, &sd_cli );

	}

	close (sd);

}

void *cliente (void *arg) {

	int sdc;
	int n;

	int threadType=0;
	
	
	sdc = *( (int *) arg);

	#ifdef DEBUG
	printf("--------------------------------\n");
	printf("Nuevo Cliente:%i \n",sdc);
	#endif

	n = 1;
	while ( (n != 0)) {

	protocoloCMD *mjs;
	mjs = (protocoloCMD*) malloc(sizeof(protocoloCMD));

	n = leer_mensaje(sdc, mjs);

	if( n > 0)
		{
			switch (mjs->header.codigo)
			{
				case SOLICITUD_SIGN_IN:
				{
					printf("Cliente say: %s\n", mjs->body.mensage);	
					enviar_mensaje(sdc,ACK_SIGN_IN,"Enviar tu datos");
			        
					
				free(mjs);
					break;
				}
				case LOGGIN_USER:
				{
				printf("Loggin");
				char *usuario=strtok(mjs->body.mensage,",");
				char *password=strtok(NULL,",");
				
				if (buscar_usuario(usuario,password)>0){
					enviar_mensaje(sdc,USER_VALID,"Usuario Loggeado con exisito");
				}else{
					enviar_mensaje(sdc,USER_ERROR,"No es un usuario valido");					
				}
				free(mjs);
				break;
				}

				case EXIT_COMANDO:
				{
					n=0;

				free(mjs);
				break;
				}
				case SOLICITUD_COMANDO:
				{
					char *std_result=NULL;	
					printf("%s",mjs->body.mensage);	
					sleep(3);		
					std_result = executeComand(mjs->body.mensage);
					enviar_mensaje(sdc,RESPUESTA_COMANDO,std_result);

				free(mjs);
				break;
				}
				
			    default:
					{


						break;
					}

			}
		}
		

	}
close(sdc);
}


