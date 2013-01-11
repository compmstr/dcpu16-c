#include<stdio.h>
#include<curses.h>
#include<string.h>
#include"vm.h"
#include"compiler.h"
#include <unistd.h>

int main(int argc, char **argv){
	initscr();
	cbreak();
	noecho();

	char input;
	char buf1[256];
	char buf2[256];
	while(1){
		clear();
		printw("Menu:\n--------------\n1) Compile\n2) Run\nq) Exit\n----------\n> ");
		input = getch();
		if(input == '1'){
			clear();
			printw("Compiling: \n");
			printw("Enter file to compile (test.dasm) : ");

			echo();
			refresh();
			getnstr(buf1, 255);
			printw("Enter file to output (test.dbin) : ");
			refresh();
			getnstr(buf2, 255);

			noecho();

			if(strlen(buf1) == 0){
				strncpy(buf1, "test.dasm", 100);
			}
			if(strlen(buf2) == 0){
				strncpy(buf2, "test.dbin", 100);
			}

			printw("Compiling %s to %s\n", buf1, buf2);
			refresh();

			printw("Press any key to continue");
			refresh();
			getch();
		}
		if(input == '2'){
			clear();
			printw("Running: \n");
			refresh();
			sleep(1);
		}
		if(input == 'q'){
			clear();
			printw("Exiting... \n");
			refresh();
			break;
		}
	}

	endwin();
	
  return 0;
}
