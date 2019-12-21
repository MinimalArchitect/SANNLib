CC = gcc

DEFS = -D_DEFAULT_SOURCE -D_POSIX_C_SOURCE=200809L
CFLAGS = -Wall -g -std=c99 -pedantic $(DEFS)

OBJECTS = main.o vector.o matrix.o

.PHONY: all clean

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c
vector.o: vector.c
matrix.o: matrix.c

clean:
	rm -rf *.o main
