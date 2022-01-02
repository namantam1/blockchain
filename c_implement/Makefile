CC=gcc
CFLAGS=-Wall -g
BIN=sha256
SOURCE=main

all: $(SOURCE)

%.o: %.c %.h
	$(CC) -c $< -o $@

$(SOURCE): $(SOURCE).c $(BIN).o
	$(CC) $(CFLAGS) $^ -o $@.out

clean:
	rm -rf *.o *.out *.exe
