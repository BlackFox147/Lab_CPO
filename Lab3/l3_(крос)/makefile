CC = gcc
CFLAGS = -c -Wall -pedantic
STAND:=  -std=c99

ifeq ($(OS), Windows_NT)

server: win.o main.o Write_ser win_client
	$(CC) win.o main.o -o server

win.o: win.c
	$(CC) $(CFLAGS) $(STAND) win.c

win_client: win_client.o main.o Write_cl 
	$(CC) win_client.o main.o -o win_client
	
win_client.o: win_client.c
	$(CC) $(CFLAGS) $(STAND) win_client.c

main.o: main.c
	$(CC) $(CFLAGS) $(STAND) main.c
	
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

server_lin: ser_lin.o main.o client_lin
	$(CC) ser_lin.o main.o -o server_lin

ser_lin.o: ser_lin.c
	$(CC) $(CFLAGS) $(STAND) ser_lin.c
	
client_lin: cl_lin.o main.o
	$(CC) cl_lin.o main.o -o client_lin

cl_lin.o: cl_lin.c
	$(CC) $(CFLAGS) $(STAND) cl_lin.c

main.o: main.c
	$(CC) $(CFLAGS) $(STAND) main.c
	
clean:
	 rm -f *.o
	 rm -f lab2_lin
	
endif

