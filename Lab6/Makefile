CC = gcc
CFLAGS = -c -Wall -pedantic

APP = lb6


SHAREDFLAG = -shared

STAND:=  -std=gnu99



MAIN_SOURCES = main.c
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)



all: $(APP)


$(APP): $(MAIN_OBJECTS)
	$(CC) $(MAIN_OBJECTS) $(STAND) -o $@ -ldl -pthread 
	
.c.o:
	$(CC) $(CFLAGS) $(STAND) $< -o $@

.PHONY: clean
clean:
	rm -rf $(APP)
	rm -rf *.o