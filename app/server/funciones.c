/*Fecha de ultima Modificacion 26/04/2015*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PATH_USUARIOS /home/boga/comando/app/build/usuarios.txt
#define modo r


int buscar_usuario(char *usuario,char *password){
	FILE *fd;
	fd=fopen("/home/boga/comando/app/build/usuarios.txt","r");
	char *user=NULL;
	char *pass=NULL;
	char *line=NULL;
	size_t len=0;
	ssize_t read=0;
	int estado=0;
	
	printf("%s-%s",usuario,password);		
	if (fd==NULL){
		
		estado=-1;		
	}else{
	
		while (read=getline(&line,&len,fd)!=-1 ){
			
			if (read > 0){			
				user=strtok(line,",");
			
				pass=strtok(NULL,",");

				
				if ( strcmp(user,usuario)==0 && strncmp(pass,password,strlen(pass)-1)==0 ) 
					estado=1;
			}
									
								
			
		}
	
	}

		if (user!=NULL)
			free(user);
		if (pass!=NULL)
			free(pass);
					
		if (line!=NULL)
			//free(line);
		close(fd);
				
	return estado;
}

char* executeComand(char *comando)
{		
		system ( "clear" );
		#ifdef DEBUG
		printf("execute comando");
		#endif
	      	FILE *in;
		char *std_out=NULL;
		char buffer[80];
		
		#ifdef DEBUG
		printf("COMANDO-%s",comando);
		#endif
		if ( !( in = popen ( comando, "r" ) ) ) {
	  		printf("NO ejecuto");
		}

		int i=1,size=0;				
		while ( fgets ( buffer,  sizeof(char) * 80 , in ) != NULL){
			size = sizeof(char)*80;
			std_out=realloc(std_out,(size*i)+2);
			strcat(std_out,buffer);
			i++;
			
		}
		pclose(in);	
		
		return std_out;
	
	

}

