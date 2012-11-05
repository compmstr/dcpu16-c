#ifndef __VM_H__
#define __VM_H__

#include "codes.h"

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
	LOC_IA,
};

typedef struct vm_loc_t {
	enum vm_loc_type type;
	unsigned short loc;
	unsigned short reg;
	unsigned short val;
}vm_loc;


extern unsigned short ram[0x10000];
extern unsigned short registers[8];
extern unsigned short SP;
extern unsigned short PC;
extern unsigned short EX;
extern unsigned short IA;


void init_vm();
unsigned short get_next_word();
unsigned short code_word_op(const unsigned short word);
vm_loc code_word_a(const unsigned short word);
vm_loc code_word_b(const unsigned short word);

unsigned short get_value(const vm_loc *loc);
void set_value(const vm_loc *loc, const unsigned short val);

unsigned short mem_get(const unsigned short loc);
void mem_set(const unsigned short loc, const unsigned short val);

/**
	 Write code into ram starting at loc
	 Code is in a short array (code), with length len
**/
void write_code(const unsigned short loc, const unsigned short *code, const unsigned short len);

/**
	 Reads the next code word ([PC++]), and executes it
**/
void vm_step();

#endif
