#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "codes.h"

#define MAX_LINE 256

extern input_file *input_file_stack;

char *parser_get_orig_line();
bool open_input(const char* filename);
void close_input();
unsigned char is_input_open();
void read_input_line();
token *get_next_token(token *tok);

#endif
