CC = gcc
CFLAGS = -c -Wall -pedantic
STAND:=  -std=c99

ifeq ($(OS), Windows_NT)

server: server.o client Write_ser
	$(CC) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) $(STAND) server.c
	
client: client.o Write_cl
	$(CC) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) $(STAND) client.c
	
Write_ser: Write_ser.o 
	$(CC) Write_ser.o -o Write_ser

Write_ser.o: Write_ser.c
	$(CC) $(CFLAGS) $(STAND) Write_ser.c	
	
Write_cl: Write_cl.o 
	$(CC) Write_cl.o -o Write_cl

Write_cl.o: Write_cl.c
	$(CC) $(CFLAGS) $(STAND) Write_cl.c
	
clean:
	 del /f /q *.o
	 del /f /q *.exe
	 
else

STAND:=  -std=gnu99

server_lin: server_linux.o client_lin
	$(CC) server_linux.o -o server_lin

server_linux.o: server_linux.c
	$(CC) $(CFLAGS) $(STAND) server_linux.c
	
client_lin: client_linux.o
	$(CC) client_linux.o -o client_lin

client_linux.o: client_linux.c
	$(CC) $(CFLAGS) $(STAND) client_linux.c
	
clean:
	 rm -f *.o
	 rm -f lab2_lin
	
endif

