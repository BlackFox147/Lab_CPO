CC = gcc
CFLAGS = -c -Wall -pedantic

ifeq ($(OS), Windows_NT)

STAND:=  -std=c99

lab2_win: main.o mainW win.o stack.o
	$(CC) main.o win.o stack.o -o lab2_win

main.o: main.c
	$(CC) $(CFLAGS) $(STAND) main.c

mainW.o: mainW.c
	$(CC) $(CFLAGS) $(STAND) mainW.c

mainW: mainW.o
	$(CC) mainW.o -o mainW
	
win.o: win.c
	$(CC) $(CFLAGS) $(STAND) win.c
	
stack.o: stack.c
	$(CC) $(CFLAGS) $(STAND) stack.c
	
clean:
	 del /f /q *.o
	 del /f /q *.exe
	
	
else

STAND:=  -std=gnu99

lab2_lin: main.o lin.o stack.o
	$(CC) main.o lin.o stack.o -o lab2_lin


main.o: main.c
	$(CC) $(CFLAGS) $(STAND) main.c

	
lin.o: lin.c
	$(CC) $(CFLAGS) $(STAND) lin.c
	
stack.o: stack.c
	$(CC) $(CFLAGS) $(STAND) stack.c	

clean:
	 rm -f *.o
	 rm -f lab2_lin
	
endif




	
	
	


