#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdio.h>

enum vm_loc_type {
	LOC_REGISTER,
	LOC_MEMORY,
	LOC_REGISTER_MEMORY,
	LOC_REGISTER_MEMORY_OFFSET,
	LOC_PUSHPOP, 
	LOC_PEEK,
	LOC_PICK, 
	LOC_LITERAL,
	LOC_SP,
	LOC_PC,
	LOC_EX,
	LOC_LABEL,
	LOC_LABEL_MEM,
	LOC_IA,
};

enum codelist_entry_type {
	CODELIST_ENTRY_TYPE_OP,
	CODELIST_ENTRY_TYPE_SPECIAL_OP,
	CODELIST_ENTRY_TYPE_LABEL,
	CODELIST_ENTRY_TYPE_DATA,
};

typedef struct vm_loc_t {
	enum vm_loc_type type;
	unsigned short loc;
	unsigned short reg;
	unsigned short val;
}vm_loc;

typedef struct token_val_t{
	enum vm_loc_type type;
	unsigned short reg;
	unsigned short loc;
	unsigned short val;
	char *label_name;
}token_val;

typedef struct code_label_t{
	char *label_name;
	unsigned short loc;
	struct code_label_t *next;
}code_label;

typedef struct codelist_entry_t {
	enum codelist_entry_type type;
	unsigned short op;
	token_val *aval;
	token_val *bval;
	code_label *label;
	unsigned short *data;
	unsigned short *data_size;
	unsigned short codeloc;
	struct codelist_entry_t *next;
}codelist_entry ;

typedef struct input_file_t{
	char *line_buffer;
	char *orig_line_buffer;
	unsigned int line_buffer_len;
	unsigned int line_buffer_pos;
	FILE *fd;
	struct input_file_t *next;
}input_file;

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef Uint8 bool;

#endif
