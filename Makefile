CC=gcc
#CFLAGS=-O3 -Wall `sdl-config --cflags`
#CFLAGS=-std=c99 -Wall -ggdb -pg `sdl-config --cflags`
CFLAGS=-std=c99 -Wall -ggdb `sdl-config --cflags`
LIBS=-L/usr/X11/lib `sdl-config --libs` -lncurses

dcpu16-c: src/main.c vm.o compiler.o encoder.o parser.o token_val.o codelist_entry.o types
	$(CC) $(CFLAGS) -c src/main.c
	$(CC) $(CFLAGS) vm.o encoder.o compiler.o parser.o token_val.o codelist_entry.o $(LIBS) main.o -o dcpu16-c
vm.o: src/vm.h src/vm.c src/codes.h
	$(CC) $(CFLAGS) -c src/vm.c
compiler.o: src/compiler.h src/compiler.c
	$(CC) $(CFLAGS) -c src/compiler.c
parser.o: src/parser.h src/parser.c
	$(CC) $(CFLAGS) -c src/parser.c
token_val.o: src/token_val.h src/token_val.c
	$(CC) $(CFLAGS) -c src/token_val.c
codelist_entry.o: src/codelist_entry.h src/codelist_entry.c
	$(CC) $(CFLAGS) -c src/codelist_entry.c
encoder.o: src/encoder.h src/encoder.c
	$(CC) $(CFLAGS) -c src/encoder.c
types: src/types.h
	echo 'processing types...'

test: src/test.c
	$(CC) $(CFLAGS) -o test src/test.c

clean:
	rm -f *.o dcpu16-c test
