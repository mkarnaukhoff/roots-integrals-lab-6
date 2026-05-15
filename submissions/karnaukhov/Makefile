CC=gcc
CFLAGS=-O2 -std=c11 -Wall -Wextra
LDFLAGS=-lm

all: lab6

lab6: src/main.o src/methods.o src/functions.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o lab6