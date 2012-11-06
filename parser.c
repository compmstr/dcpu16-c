#include "parser.h"

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
		//TODO
	}
}
char *parser_get_orig_line(){
	return 0;
}
bool open_input(const char* filename){
	return push_input_file(filename);
}
void close_input(){
	pop_input_file();
}

bool is_input_open(){
	return 0;
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
void read_input_line(){
	fgets(input_file_stack->orig_line_buffer, MAX_LINE, input_file_stack->fd);
	strncpy(input_file_stack->line_buffer,
					input_file_stack->orig_line_buffer,
					// need to leave room for \0
					strlen(input_file_stack->orig_line_buffer) + 1);
}
token *get_next_token(token *tok){
	return tok;
}

