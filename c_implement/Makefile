CC=gcc
CFLAGS=-Wall -g
LOADLIBES=blockchain.o sha256.o
SOURCE=main

all: $(LOADLIBES) $(SOURCE)

debug: CFLAGS+=-DDEBUG
debug: $(LOADLIBES)
	$(CC) $(CFLAGS) $(LOADLIBES) -o debug

clean:
	rm -f *.o *.out *.exe test $(SOURCE)
