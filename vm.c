#include "vm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


unsigned short ram[0x10000];
unsigned short registers[8];
unsigned short SP;
unsigned short PC;
unsigned short EX;
unsigned short IA;

void init_vm(){
  memset(ram, 0, sizeof(short) * 0x10000);
  PC = 0;
  SP = 0xFFFF;
  EX = 0;
  IA = 0;

  unsigned short test_code[] = {
        0x7c01, 0x0030,
				0x7fc1, 0x0020, 0x1000,
				0x7803, 0x1000,
				0xc013,
				0x7f80, 0x0020
  };
	write_code(0, test_code, sizeof(test_code));
}
unsigned short peek_next_word(){
	return mem_get(PC);
}
unsigned short get_next_word(){
  return mem_get(PC++);
}
unsigned short code_word_op(unsigned short word){
  //Bottom 5 bits
  return word & 0x1f;
}

void set_value(const vm_loc *loc, const unsigned short val){
	if(loc == 0){
		return;
	}
	switch(loc->type){
	case LOC_REGISTER:
		registers[loc->reg] = val;
		break;
	case LOC_MEMORY:
		mem_set(loc->loc, val);
		break;
	case LOC_REGISTER_MEMORY:
		mem_set(registers[loc->reg], val);
		break;
	case LOC_REGISTER_MEMORY_OFFSET:
		mem_set(registers[loc->reg] + loc->loc, val);
		break;
	case LOC_SP:
		SP = val;
		break;
	case LOC_EX:
		EX = val;
		break;
	case LOC_PC:
		PC = val;
		break;
	case LOC_IA:
		IA = val;
		break;
	case LOC_PUSHPOP:
		// Push
		mem_set(--SP, val);
		break;
	case LOC_PEEK:
		mem_set(SP, val);
		break;
	case LOC_PICK:
		mem_set(SP + loc->loc, val);
		break;
	case LOC_LITERAL:
		break;
	}
	//Fail silently otherwise
}

unsigned short get_value(const vm_loc *loc){
	if(loc == 0){
		return 0;
	}
	switch(loc->type){
	case LOC_REGISTER:
		return registers[loc->reg];
		break;
	case LOC_MEMORY:
		return mem_get(loc->loc);
		break;
	case LOC_REGISTER_MEMORY:
		return mem_get(registers[loc->reg]);
		break;
	case LOC_REGISTER_MEMORY_OFFSET:
		return mem_get(registers[loc->reg] + loc->loc);
		break;
	case LOC_LITERAL:
		return loc->val;
		break;
	case LOC_SP:
		return SP;
		break;
	case LOC_PC:
		return PC;
		break;
	case LOC_EX:
		return EX;
		break;
	case LOC_IA:
		return IA;
		break;
	case LOC_PUSHPOP:
		// Pop
		return mem_get(SP++);
		break;
	case LOC_PICK:
		return mem_get(loc->reg + SP);
		break;
	case LOC_PEEK:
		return mem_get(SP);
		break;
	}
	return 0;
}

/*takes the 5/6 bit value and returns the actual value
  raw_val - 5/6 bit value
  b_val - true/1 if we're looking up b, false/0 if looking up a*/
vm_loc code_word_value(unsigned short raw_val, const short b_val){
	vm_loc ret;
	//Register
	if(raw_val <= 0x07){
		ret.type = LOC_REGISTER;
		ret.reg = raw_val;
	}else if(raw_val <= 0x0f){
	//[Register]
		ret.type = LOC_REGISTER_MEMORY;
		ret.reg = raw_val % 0x08;
	} else if(raw_val <= 0x17){
	//[Register + next word]
		ret.type = LOC_REGISTER_MEMORY_OFFSET;
		ret.reg = raw_val % 0x08;
		ret.loc = get_next_word();
	}
	switch(raw_val){
	//PUSH [--SP] if in b, or POP [SP++] if in a
	case 0x18:
		ret.type = LOC_PUSHPOP;
		break;
	//PEEK [SP]
	case 0x19:
		ret.type = LOC_PEEK;
		break;
	//PICK [SP + next word]
	case 0x1a:
		ret.type = LOC_PICK;
		ret.loc = get_next_word();
		break;
	//SP
	case 0x1b:
		ret.type = LOC_SP;
		break;
	//PC
	case 0x1c:
		ret.type = LOC_PC;
		break;
	//EX
	case 0x1d:
		ret.type = LOC_EX;
		break;
	//[next word]
	case 0x1e:
		ret.type = LOC_MEMORY;
		ret.loc = get_next_word();
		break;
	//next word (literal)
	case 0x1f:
		ret.type = LOC_LITERAL;
		ret.val = get_next_word();
	}
	//literal value (a only)
	if(!b_val && raw_val >= 0x20){
		ret.type = LOC_LITERAL;
		ret.val = raw_val - 0x20;
	}

	return ret;
}

vm_loc code_word_a(unsigned short word){
  //Bits from 11-16
  short raw_a = word >> 10;
  return code_word_value(raw_a, FALSE);
}
vm_loc code_word_b(unsigned short word){
  //Bits from 5-10
  short raw_b = (word >> 5) & 0x1f;
  return code_word_value(raw_b, TRUE);
}

unsigned short mem_get(unsigned short loc){
  return ram[loc];
}

void mem_set(unsigned short loc, unsigned short val){
  ram[loc] = val;
}

/**
	 Write code into ram starting at loc
	 Code is in a short array (code), with length len
**/
void write_code(const unsigned short loc, const unsigned short *code, const unsigned short len){
	for(int i = 0; i < len; i++){
		ram[loc + i] = code[i];
	}
}

/**
	 For IF_ ops, skip next code word
**/
void vm_skip(){
	printf("SKIP\n");
	unsigned short word = get_next_word();
	unsigned short op = code_word_op(word);
	if(op == OP_SPECIAL){
    code_word_a(word);
	}else{
		code_word_a(word);
		code_word_b(word);
	}
}

void run_special_op(const unsigned short word){
}

void run_op(const unsigned short word){
	unsigned short op = code_word_op(word);
	if(op == OP_SPECIAL){
		run_special_op(word);
	}
	vm_loc a = code_word_a(word);
	vm_loc b = code_word_b(word);
	switch(op){
	case OP_SET:
		printf("OP_SET\n");
		set_value(&b, get_value(&a));
		break;
	case OP_ADD:
		printf("OP_ADD\n");
		set_value(&b, get_value(&b) + get_value(&a));
		break;
	case OP_SUB:
		printf("OP_SUB\n");
		set_value(&b, get_value(&b) - get_value(&a));
		break;
	case OP_IFN:
		printf("OP_IFN\n");
		printf("A: 0x%04X -- B: 0x%04X\n", get_value(&a), get_value(&b));
		if(get_value(&a) == get_value(&b)){
			vm_skip();
		}
		break;
	}
}

/**
	 Reads the next code word ([PC++]), and executes it
**/
void vm_step(){
	unsigned short word = get_next_word();
	run_op(word);
}
