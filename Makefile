CC=gcc
#CFLAGS=-O3 -Wall `sdl-config --cflags`
#CFLAGS=-std=c99 -Wall -ggdb -pg `sdl-config --cflags`
CFLAGS=-std=c99 -Wall -ggdb `sdl-config --cflags`
LIBS=-L/usr/X11/lib `sdl-config --libs`

dcpu16-c: main.c vm.o compiler.o parser.o types
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) vm.o compiler.o parser.o $(LIBS) main.o -o dcpu16-c
vm.o: vm.h vm.c codes.h
	$(CC) $(CFLAGS) -c vm.c
compiler.o: compiler.h compiler.c
	$(CC) $(CFLAGS) -c compiler.c
parser.o: parser.h parser.c
	$(CC) $(CFLAGS) -c parser.c
types: types.h
	echo 'processing types...'

clean:
	rm main.o vm.o dcpu16-c
