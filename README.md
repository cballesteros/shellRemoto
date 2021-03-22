# Shell remoto

Integrantes:
Cristian Ballesteros
Alejandro Muñoz

 Código modificado del proyecto del profesor John Sanabria:
 https://github.com/josanabr/ProyectoShellRemoto

En este repositorio se encuentra el desarrollo de un shell remoto que sigue el esquema cliente/servidor.
La siguiente gráfica muestra lo que se espera sea la interacción entre el shell cliente y el servidor. 

<img src="figures/MiniShellRemoto.png" alt="Mini Shell Remoto Cliente/Servidor" width="650"/>

Al lado derecho de la gráfica se observa el servidor quien está esperando por peticiones de un cliente.
Este servidor espera recibir comandos a través de la red de parte de un proceso cliente.

El cliente es un proceso que está en espera de leer por teclado un comando y una vez recibido ese comando, se envía al servidor.
El cliente creará un hijo quien se encarga de interactuar con el servidor, enviar el comando y esperar por la respuesta del comando.
Una vez este proceso hijo reciba la respuesta del servidor, imprime la respuesta y termina su ejecución.
El cliente (padre) volverá a presentar el *prompt* (`>`) y quedará en espera del siguiente comando por parte del usuario.

El servidor al recibir una solicitud a través de la red, crea un proceso hijo quien se encargará de procesar dicha solicitud. 
El proceso hijo recibe la solicitud y la ejecuta con la función `execvp` o alguna de las funciones miembros de la familia `exev*`.
El proceso (padre) toma la salida del proceso hijo y la envía al lado del cliente.

---

### `basic_client` y `basic_server` 

Para ver en operación el shell remoto se debe ejecutar el comando `make shell` que se encarga de compilar los archivos objeto que requiere este aplicativo (`tcp.o`, `leercadena.o`) y el cliente (`basic_client`) y el servidor (`basic_server`). 

Para ejecutar el servidor ejecute el comando `./basic_server 12358`. 

Abra otra terminal y en ella ejecute el cliente de la siguiente manera `./basic_client localhost 12358`.

El cliente abrirá un promt para que el usuario digite algún comando y este será enviado al servidor. Una vez ejecutado el comando en el lado del servidor, el cliente mostrará la respuesta y dejará abierto el promt para que el usuario pueda digitar otro comando.

Algunos comandos de ejemplo:

* ps
* pwd
* ls -R
* ls -a
* ls -al
* ls ../ | grep sirena

* touch hola.txt
* echo Hello this is a remote shell >> hola.txt
* cat hola.txt
* rm hola.txt
