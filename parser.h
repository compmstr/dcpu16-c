#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "codes.h"

#define MAX_LINE 256

extern input_file *input_file_stack;

void eat_whitespace();
char *parser_get_line();
char *parser_get_orig_line();
bool open_input_m4(const char* filename);
bool open_input(const char* filename);
void close_input();
unsigned char is_input_open();
/**
	 Reads the next input line, returns true if not end of file
**/
bool read_input_line();
char *get_next_token();

bool is_square_bracketed(const char *str);
bool is_string_number(const char *str);
/* returns 10 or 16, based on if the string starts with 0x or not */
int  get_string_number_base(const char *str);

void str_to_upper(char *str);

bool is_line_comment();
bool is_line_dat();
bool is_line_include();
bool is_line_blank();
bool is_line_label();

char *get_rest_of_line();
char *get_rest_of_orig_line();
char *get_include_filename();

#endif
