CC = gcc
CFLAGS = -c -Wall -pedantic
STAND:=  -std=c99
TARGET = lab4

ifeq ($(OS), Windows_NT)

SOURCES = main.c laba_win.c
OBJECTS = $(SOURCES:.c=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(STAND) -o $@

.c.o:
	$(CC) $(CFLAGS) $(STAND) $< -o $@

.PHONY: clean
clean:
	del $(TARGET).exe $(OBJECTS)

else

SOURCES = main.c laba_linux.c
OBJECTS = $(SOURCES:.c=.o)
UNIXFLAG = -D_XOPEN_SOURCE=600
THREADFLAG = -pthread

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(THREADFLAG) $(OBJECTS) $(STAND) -o $@

.c.o:
	$(CC) $(THREADFLAG) $(CFLAGS) $(UNIXFLAG) $(STAND) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)
	
endif
