# project	verticalize
# file		Makefile

CC=gcc
CFLAGS=-W -Wall -O3 -std=c18
LDFLAGS=

EXEC=verticalize
SRC=$(wildcard src/*.c)
OBJ=$(SRC:*.c=*.o)

all: $(EXEC)

verticalize: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf src/*.o
	rm $(EXEC)
