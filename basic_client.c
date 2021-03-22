/**
 * Programa principal del cliente.
 * Encargado de enviar peticiones a través de un puerto.
 * 
 * Código modificado del proyecto del profesor John Sanabria:
 * https://github.com/josanabr/ProyectoShellRemoto
 * 
 * Autor: Cristian Ballesteros
 * Autor: Alejandro Muñoz
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <limits.h>
#include "tcp.h"
#include "leercadena.h"

#define MAX 256

void func(int sockfd) 
{
	int pid, status, childPid;
	char comando[_POSIX_ARG_MAX];
	char buffResponse[_POSIX_ARG_MAX];

	while (strcmp(comando, "exit") != 0)
	{
		bzero(comando, _POSIX_ARG_MAX);
		bzero(buffResponse, _POSIX_ARG_MAX);

		printf("Digite su comando: $ ");
		leer_de_teclado(_POSIX_ARG_MAX,comando);
		puts(comando);

		pid = fork();

		if (pid == 0)
		{
			//Proceso hijo envía la solicitud al servidor
			TCP_Write_String(sockfd, comando);
			exit(0);
		}
		else
		{
			//Proceso padre espera por el resultado e imprime la respuesta
			childPid = wait(&status);
			if (status == 0)
			{
				TCP_Read_String(sockfd, buffResponse, _POSIX_ARG_MAX);
				printf("Respuesta del servidor: \n%s\n", buffResponse);
			}
			else
			{
				printf("\nOcurrió un error del lado del servidor\n");
			}
		}
	}
} 

int main(int argc, char* argv[]) 
{ 
	int sockfd, port; 
	char *host;

	if (argc != 3) {
		printf("Uso: %s <host> <puerto>\n",argv[0]);
		return 1;
	}
	host = argv[1];
	port = atoi(argv[2]);

	printf("Looking to connect at <%s,%d>\n",host,port);
	sockfd = TCP_Open(Get_IP(host),port);
	// function for chat 
	func(sockfd); 

	// close the socket 
	close(sockfd); 
} 

