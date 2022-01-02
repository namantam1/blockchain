CC=gcc
CFLAGS=-Wall -g
LOADLIBES=sha256.o
SOURCE=main

all: $(SOURCE)

sample: $(LOADLIBES) test

# Not Needed its a implicit rule
# %.o: %.c %.h
# 	$(CC) -c $< -o $@

$(SOURCE): $(SOURCE).c $(LOADLIBES)
	$(CC) $(CFLAGS) $^ -o $@.out

clean:
	rm -f *.o *.out *.exe test $(SOURCE)
