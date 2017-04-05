server: server.o client
	gcc server.o -o server

server.o: server.c
	gcc -c -Wall -pedantic -std=gnu99 server.c
	
client: client.o
	gcc client.o -o client

client.o: client.c
	gcc -c -Wall -pedantic -std=gnu99 client.c