#include <math.h>
#include"compiler.h"
#include "types.h"
#include "parser.h"
#include "codelist_entry.h"

codelist_entry *codelist = 0;
codelist_entry *codelist_end = 0;
code_label *labels = 0;

void compile_cleanup(){
	codelist_entry *cl = codelist;
	codelist_entry *old = 0;
	while(cl){
		if(cl->aval){
			free(cl->aval);
		}
		if(cl->bval){
			free(cl->bval);
		}
		if(cl->label){
			free(cl->label);
		}
		if(cl->data){
			free(cl->data);
		}
		old = cl;
		cl = cl->next;
		free(old);
	}
	codelist = 0;
	codelist_end = 0;
	labels = 0;
}
void compile_init(){
	compile_cleanup();
}

void add_codelist_entry(codelist_entry *new_entry){
	if(codelist == 0){
		//Empty, just set to the new one
		codelist = codelist_end = new_entry;
	}else{
		codelist_end->next = new_entry;
		codelist_end = new_entry;
	}
}

codelist_entry *process_label(){
	char *label_raw = get_next_token();

	int raw_size = strlen(label_raw);
	//Take off initial ':', and copy to new string
	char *label_name = calloc(raw_size, sizeof(char));
	strncpy(label_name, label_raw + 1, raw_size - 1);
	printf("Raw label: %s -- Label name: %s -- last char: %d\n", label_raw, label_name, (int)label_name[strlen(label_name) - 1]);

	free(label_raw);

	code_label *label = calloc(sizeof(code_label), 1);
	label->label_name = label_name;
	codelist_entry *cl = calloc(sizeof(codelist_entry), 1);
	cl->type = CODELIST_ENTRY_TYPE_LABEL;
	cl->label = label;
	return cl;
}

/*Gets up to 8 dat numbers from a string*/
void get_data_from_nums(const char *str, codelist_entry *entry){
	int *data = calloc(sizeof(int), 8);
	int size = sscanf(str, "%i %i %i %i %i %i %i %i",
										data, data + 1, data + 2, data + 3,
										data + 4, data + 5, data + 6, data + 7);
	if(size != 8 && size != 0){
		data = realloc(data, sizeof(short) * size);
	}
	if(size == 0){
		printf("Error when parsing numbers from DAT field\n");
	}
	entry->data = data;
	entry->data_size = size;
}
void get_data_from_quoted_string(char *str, codelist_entry *entry){
	remove_string_ends(str);
	int len = strlen(str);
	int size = ceil(len / 2.0f);
	int *data = calloc(sizeof(int), size);
	int tmp;
	for(int i = 0; i < size; i++){
		tmp = str[i * 2];
		tmp += str[(i * 2) + 1] << 8;
		data[i] = (tmp & 0xFFFF);
	}
	entry->data = data;
	entry->data_size = size;
}
codelist_entry *process_dat(){
	char *orig_line = get_rest_of_orig_line();
	int len = strlen(orig_line);
	char *buf = calloc(len - 3, sizeof(char));
	//Take off the DAT and following space
	strncpy(buf, orig_line + 4, len - 3);
	trim(buf);
	printf("Dat: %s\n", buf);

	codelist_entry *entry = calloc(sizeof(codelist_entry), 1);
	if(is_quoted_string(buf)){
		get_data_from_quoted_string(buf, entry);
	}else{
		get_data_from_nums(buf, entry);
	}

	printf("Data: ");
	for(int i = 0; i < entry->data_size; i++){
		printf("0x%04x ", entry->data[i]);
	}
	printf("\n");
	for(int i = 0; i < entry->data_size; i++){
		unsigned short cur = entry->data[i];
		printf("%c%c", (cur >> 8), (cur & 0xFF));
	}
	printf("\n");

	return entry;
}
codelist_entry *process_op(){
	return NULL;
}

codelist_entry *process_line(){
	eat_whitespace();
	codelist_entry *ret = NULL;
	printf("Processing line: %s -- len: %d\n", input_file_stack->line_buffer, (int)strlen(input_file_stack->line_buffer));
	if(!is_line_blank() && !is_line_comment()){
		if(is_line_label()){
			printf("Line is label\n");
			return process_label();
		}else if(is_line_dat()){
			printf("Line is data\n");
			return process_dat();
		}else if(is_line_include()){
			printf("Line is include\n");
			open_input_m4(get_include_filename());
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
	printf("Initializing compiler...\n");
	compile_init();
	open_input_m4(src);

	codelist_entry *entry;
	while(is_input_open()){
		while(read_input_line()){
			entry = process_line();
			if(entry != NULL){
				printf("Adding codelist entry...\n");
				add_codelist_entry(entry);
			}
		}
		close_input();
	}

	close_input();
	compile_cleanup();
}

