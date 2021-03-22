/**
 * Programa principal del servidor.
 * Encargado de abrir el puerto para establacer la conexión
 * y encargado de ejecutar los comandos que vienen del cliente.
 * 
 * Código modificado del proyecto del profesor John Sanabria:
 * https://github.com/josanabr/ProyectoShellRemoto
 * 
 * Autor: Cristian Ballesteros
 * Autor: Alejandro Muñoz
 */
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include "tcp.h"

#define MAX 256

void executeCommand(int sockfd, char *buff)
{
	FILE *fp;
	int pid, status, childPid;
	char path[_POSIX_ARG_MAX];
	char response[_POSIX_ARG_MAX];

	pid = fork();

	if (pid == 0)
	{
		bzero(path,_POSIX_ARG_MAX);
		bzero(response,_POSIX_ARG_MAX);

		fp = popen(buff, "r");
		if (fp == NULL) {
			TCP_Write_String(sockfd, "Error ejecutando el comando");
			perror("Error ejecutando el comando");
			exit(1);			
		}
		while (fgets(path, _POSIX_ARG_MAX, fp) != NULL)
			strcat(response, path);
		if (strcmp(response, "") != 0)
		{
			TCP_Write_String(sockfd, response);
		}
		else
		{
			TCP_Write_String(sockfd, "Comando Ejecutado con Éxito");
		}		
		pclose(fp);
		_exit(0);
	}
	else
	{
		wait(&status);
		if (status != 0)
		{
			TCP_Write_String(sockfd, "Error ejecutando el comando");
		}
		
	}
}

/**
 * Lee instrucciones del cliente y las ejecuta hasta que se lea la palabra "exit"
 */ 
void readCommand(int sockfd) 
{
	char buff[_POSIX_ARG_MAX];

	while (strcmp(buff, "exit") != 0)
	{
		bzero(buff,_POSIX_ARG_MAX);

		TCP_Read_String(sockfd, buff, _POSIX_ARG_MAX); 
		printf("Recibido: %s\n",buff);
		executeCommand(sockfd, buff);
	}
	
}

int main(int argc, char *argv[]) 
{ 
	int socket, connfd;  
	int puerto;

	if (argc != 2) {
		printf("Uso: %s <puerto>\n",argv[0]);
		return 1;
	}
	
	puerto = atoi(argv[1]);

	socket = TCP_Server_Open(puerto);

	connfd = TCP_Accept(socket);

	// Function for chatting between client and server 
	readCommand(connfd);

	// After chatting close the socket 
	close(socket);
} 

