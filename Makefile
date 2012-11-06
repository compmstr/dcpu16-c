CC=gcc
#CFLAGS=-O3 -Wall `sdl-config --cflags`
#CFLAGS=-std=c99 -Wall -ggdb -pg `sdl-config --cflags`
CFLAGS=-std=c99 -Wall -ggdb `sdl-config --cflags`
LIBS=-L/usr/X11/lib `sdl-config --libs`

dcpu16-c: main.c vm.o
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) vm.o $(LIBS) main.o -o dcpu16-c
vm.o: vm.h vm.c codes.h
	$(CC) $(CFLAGS) -c vm.c

clean:
	rm main.o vm.o dcpu16-c
