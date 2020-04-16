CC=gcc
CFLAGS+=-W -Wall -O3
LDFLAGS+=

TARGET=transpose
PREFIX=/usr/local

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all: $(TARGET)

transpose: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: install clean mrproper

install:
	@echo installing executable file to ${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	install -Dm755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf $(EXEC)
