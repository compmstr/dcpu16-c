CC=gcc
#CFLAGS=-O3 -Wall `sdl-config --cflags`
#CFLAGS=-std=c99 -Wall -ggdb -pg `sdl-config --cflags`
CFLAGS=-std=c99 -Wall -ggdb `sdl-config --cflags`
LIBS=-L/usr/X11/lib `sdl-config --libs`

dcpu16-c: main.c vm.o compiler.o parser.o token_val.o codelist_entry.o types
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) vm.o compiler.o parser.o token_val.o codelist_entry.o $(LIBS) main.o -o dcpu16-c
vm.o: vm.h vm.c codes.h
	$(CC) $(CFLAGS) -c vm.c
compiler.o: compiler.h compiler.c
	$(CC) $(CFLAGS) -c compiler.c
parser.o: parser.h parser.c
	$(CC) $(CFLAGS) -c parser.c
token_val.o: token_val.h token_val.c
	$(CC) $(CFLAGS) -c token_val.c
codelist_entry.o: codelist_entry.h codelist_entry.c
	$(CC) $(CFLAGS) -c codelist_entry.c
types: types.h
	echo 'processing types...'

clean:
	rm main.o codelist_entry.o token_val.o parser.o compiler.o vm.o dcpu16-c
