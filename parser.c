#include "parser.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

input_file *input_file_stack;

bool push_input_file(const char* filename);
void pop_input_file();

bool is_whitespace(char c){
	if(c == '\t' || c == ' ' || c == '\r' || c == '\n'){
		return TRUE;
	}
	return FALSE;
}
void eat_whitespace(){
	char *cur = input_file_stack->line_buffer + 
              input_file_stack->line_buffer_pos;
	while(is_whitespace(*cur)){
		cur = input_file_stack->line_buffer +
			input_file_stack->line_buffer_pos++;
	}
	if(input_file_stack->line_buffer_pos != 0){
		input_file_stack->line_buffer_pos--;
	}
}
char *parser_get_orig_line(){
	return input_file_stack->orig_line_buffer;
}

bool open_input_m4(const char* filename){
	char m4_filename[256];

	strncpy(m4_filename, "/tmp/", 10);
	strncat(m4_filename, filename, strlen(filename));
	strncat(m4_filename, ".m4", 10);

	char m4_command[256];

	strncpy(m4_command, "m4 ", 4);
	strncat(m4_command, filename, strlen(filename));
	strncat(m4_command, " > ", 10);
	strncat(m4_command, m4_filename, strlen(m4_filename));

	system(m4_command);

	return open_input(m4_filename);
}

bool open_input(const char* filename){
	printf("Opening file: %s\n", filename);
	return push_input_file(filename);
}
void close_input(){
	printf("Closing \n");
	pop_input_file();
}

bool is_input_open(){
	return input_file_stack ? TRUE : FALSE;
}
bool push_input_file(const char *filename){
	input_file* new_file = calloc(sizeof(input_file), 1);
	new_file->fd = fopen(filename, "r");
	if(new_file->fd){
		new_file->line_buffer = calloc(MAX_LINE, 1);
		new_file->orig_line_buffer = calloc(MAX_LINE, 1);
		new_file->next = input_file_stack;
		input_file_stack = new_file;
		return TRUE;
	}else{
		free(new_file);
		return FALSE;
	}
}
void pop_input_file(){
	input_file* old_file = 0;
	if(input_file_stack){
		fclose(input_file_stack->fd);
		free(input_file_stack->line_buffer);
		free(input_file_stack->orig_line_buffer);
		old_file = input_file_stack;
		input_file_stack = input_file_stack->next;
		free(old_file);
	}
}
bool read_input_line(){
	char *s = fgets(input_file_stack->orig_line_buffer, MAX_LINE, input_file_stack->fd);
	if(s){
		// remove trailing newline
		int len = strlen(s);
		if(s[len - 1] == '\n'){
			s[len - 1] = 0;
		}
		strncpy(input_file_stack->line_buffer,
						input_file_stack->orig_line_buffer,
						// need to leave room for \0
						strlen(input_file_stack->orig_line_buffer) + 1);
		input_file_stack->line_buffer_pos = 0;
		// convert line_buffer to all uppercase
		str_to_upper(input_file_stack->line_buffer);

		return TRUE;
	}else{
		return FALSE;
	}
}
char *get_next_token(){
	eat_whitespace();
	char *start = input_file_stack->line_buffer + input_file_stack->line_buffer_pos;
	int size = 0;
	while(!is_whitespace(start[size])){
		size++;
	}
	printf("Token size: %d\n", size);
	input_file_stack->line_buffer_pos += size;

	char *token = calloc(size, sizeof(char));
	strncpy(token, start, size);
	return token;
}

bool is_digit(const char c, const int base){
	char upper_c = toupper(c);
	if((c >= '0' && c <= '9')
		 || ((base == 16) &&
				 (upper_c >= 'A' &&
					upper_c <= 'F'))){
		return TRUE;
	}else{
		return FALSE;	
	}
}
bool is_square_bracketed(const char *str){
	return 0;
}

/* remove one char from each end of the string */
void remove_string_ends(char *str){
}
bool is_string_number(const char *str){
	int base = get_string_number_base(str);
	if(base == 16){
		str += 2;
	}
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		if(!is_digit(str[i], base)){
			return FALSE;
		}
	}
	return TRUE;
}
/* returns 10 or 16, based on if the string starts with 0x or not */
int  get_string_number_base(const char *str){
	if(str[0] == '0' && toupper(str[1]) == 'X'){
		return 16;
	}else{
		return 10;
	}
}

int get_string_as_number(const char *str){
	return (int)strtol(str, NULL, get_string_number_base(str));
}

void str_to_upper(char *str){
	char *cur = str;
	while(*cur){
		*cur = toupper(*cur);
		cur++;
	}
}

bool is_line_comment(){
	if(get_rest_of_line()[0] == ';'){
		return TRUE;
	}else{
		return FALSE;
	}
}
bool is_line_dat(){
	if(strncmp(get_rest_of_line(), "DAT", 3) == 0){
		return TRUE;
	}
	return FALSE;
}
bool is_line_include(){
	if(strncmp(get_rest_of_line(), "#INCLUDE", 8) == 0){
		return TRUE;
	}
	return FALSE;
}
char *get_include_filename(){
	return get_rest_of_orig_line() + strlen("#INCLUDE ");
}
bool is_line_blank(){
	return (strlen(get_rest_of_line()) == 0 ? TRUE : FALSE);
}
bool is_line_label(){
	if(get_rest_of_line()[0] == ':'){
		return TRUE;
	}
	return FALSE;
}

char *get_rest_of_line(){
	return input_file_stack->line_buffer +
		input_file_stack->line_buffer_pos;
}

char *get_rest_of_orig_line(){
	return input_file_stack->orig_line_buffer +
		input_file_stack->line_buffer_pos;
}
