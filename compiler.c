#include"compiler.h"
#include "types.h"
#include "parser.h"

codelist_entry *codelist = 0;

codelist_entry *process_label(){
	return NULL;
}
codelist_entry *process_dat(){
	return NULL;
}
codelist_entry *process_op(){
	return NULL;
}

codelist_entry *process_line(){
	eat_whitespace();
	codelist_entry *ret = NULL;
	printf("Processing line: %s -- len: %d\n", input_file_stack->line_buffer, strlen(input_file_stack->line_buffer));
	if(!is_line_blank() && !is_line_comment()){
		if(is_line_label()){
			printf("Line is label\n");
			return process_label();
		}else if(is_line_dat()){
			printf("Line is data\n");
			return process_dat();
		}else if(is_line_include()){
			printf("Line is include\n");
			open_input(get_include_filename());
			return NULL;
		}else{
			printf("Processing code line\n");
			return process_op();
		}
	}else{
		printf("Line comment/empty/blank\n");
	}
	return ret;
}

void compile_file(const char *src, const char *dest){
	printf("Compiling file: %s into %s\n", src, dest);
	open_input(src);

	codelist_entry *entry;
	while(is_input_open()){
		while(read_input_line()){
			entry = process_line();
			if(entry != NULL){
			}
		}
		close_input();
	}

	close_input();
}

