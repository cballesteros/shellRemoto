all: shell

shell: basic_client basic_server

basic_client: tcp.o leercadena.o
	gcc -o basic_client basic_client.c tcp.o leercadena.o

basic_server: tcp.o
	gcc -o basic_server basic_server.c tcp.o

tcp.o:
	gcc -c tcp.c

leercadena.o:
	gcc -c leercadena.c

clean:
	rm -f *.o basic_client basic_server
