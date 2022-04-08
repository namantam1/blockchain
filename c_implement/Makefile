CC=gcc
CFLAGS=-Wall -g
LOADLIBES=blockchain.o sha256.o
SOURCE=main

all: $(LOADLIBES) $(SOURCE)

debug: CFLAGS+=-DDEBUG
debug: blockchain_dynamic.c sha256.o
	$(CC) $(CFLAGS) sha256.o $< -o debug

clean:
	rm -f *.o *.out *.exe test $(SOURCE)
