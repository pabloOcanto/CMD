/*Fecha de ultima Modificacion 26/04/2015*/
/*
ARCHIVO DE DEFINICION DE PROTOCOLO.
En este archivo se define el protocolo de alto nivel para comunicar nuestra app.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>



//DECLARACION DE LA ESTRUCTURA DEL MENSAJE
#define HEADER_LENGHT sizeof(headerCMD)
#define SOLICITUD_SIGN_IN 101
#define LOGGIN_USER 102
#define SOLICITUD_COMANDO 103


#define ACK_SIGN_IN 401
#define USER_VALID 402
#define USER_ERROR 403 
#define RESPUESTA_COMANDO 404
#define EXIT_COMANDO 502

//.....................................................


typedef struct header
{
  int codigo;
  uint32_t lenght; //corresponde a la longitud total del mensaje

} headerCMD;

typedef struct body
{
  char * mensage;
} bodyCMD;

typedef struct protocolo
{
    headerCMD header;
    bodyCMD body;
} protocoloCMD;

//DEFINICIONES DE LAS FUNCIONES PARA LOS MENSAJES
//.....................................................

int leerBytes(int sd, void *buffer, int len);
int leer_mensaje(int sd, protocoloCMD *mjs);
uint16_t enviar_mensaje(int sd, int codigo, char * mensajes);
