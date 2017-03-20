lab2_win: main.o mainW win.o stack.o
	gcc main.o win.o stack.o -o lab2_win

main.o: main.c
	gcc -c -Wall -pedantic -std=c99 main.c

mainW.o: mainW.c
	gcc -c -Wall -pedantic -std=c99 mainW.c

mainW: mainW.o
		gcc mainW.o -o mainW
	
win.o: win.c
	gcc -c -Wall -pedantic -std=c99 win.c
	
stack.o: stack.c
	gcc -c -Wall -pedantic -std=c99 stack.c
	
	
	


