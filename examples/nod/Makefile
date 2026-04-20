all: prog

prog: main.o nod.o
	gcc -m32 -o prog main.o nod.o

main.o: main.c
	gcc -m32 -c -o main.o main.c
	
nod.o: nod.asm
	nasm -f elf32 -o nod.o nod.asm

clean:
	rm -rf *.o prog

