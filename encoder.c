#include "encoder.h"
#include <stdlib.h>
#include <string.h>

op_convert_entry *op_convert_table = 0;
op_convert_entry *special_op_convert_table = 0;

#define add_op(op_name, op_code)\
	len = strlen((op_name));\
	buf = calloc(sizeof(char), len);\
	strncpy(buf, ((op_name)), len);\
	cur_op->name = buf;\
	cur_op->code = (op_code);\
	cur_op++

void init_encoder(){
	op_convert_table = calloc(sizeof(op_convert_entry), 0x20);
	special_op_convert_table = calloc(sizeof(op_convert_entry), 0x20);
	int len = 0;
	char *buf = 0;
	op_convert_entry *cur_op = op_convert_table;
	add_op("SET", 0x01);
	add_op("ADD", 0x02);
	add_op("SUB", 0x03);
	add_op("MUL", 0x04);
	add_op("MLI", 0x05);
	add_op("DIV", 0x06);
	add_op("DVI", 0x07);
  add_op("MOD", 0x08);
  add_op("MDI", 0x09);
  add_op("AND", 0x0a);
  add_op("BOR", 0x0b);
  add_op("XOR", 0x0c);
  add_op("SHR", 0x0d);
  add_op("ASR", 0x0e);
  add_op("SHL", 0x0f);
  add_op("IFB", 0x10);
  add_op("IFC", 0x11);
  add_op("IFE", 0x12);
  add_op("IFN", 0x13);
  add_op("IFG", 0x14);
  add_op("IFA", 0x15);
  add_op("IFL", 0x16);
  add_op("IFU", 0x17);
  add_op("ADX", 0x1a);
  add_op("SBX", 0x1b);
  add_op("STI", 0x1e);
  add_op("STD", 0x1f);

	cur_op = special_op_convert_table;
  add_op("JSR", 0x01);
  add_op("INT", 0x08);
  add_op("IAG", 0x09);
  add_op("IAS", 0x0a);
  add_op("RFI", 0x0b);
  add_op("IAQ", 0x0c);
  add_op("HWN", 0x10);
  add_op("HWQ", 0x11);
  add_op("HWI", 0x12);

}
unsigned short encode_op(const char *str){
	return 0;
}
unsigned short encode_val(const char *str, bool aval){
	return 0;
}
