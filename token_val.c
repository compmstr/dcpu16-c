#include "token_val.h"

/**
 * returns the size of a tokenval, from 0 to 1, whether it uses the next word or not
 *
 **/
int token_val_size(token_val *val, bool a_mode){
	switch(val->type){
	case LOC_REGISTER_MEMORY_OFFSET:
	case LOC_PICK:
	case LOC_MEMORY:
	case LOC_LABEL:
	case LOC_LABEL_MEM:
		return 1;
	case LOC_LITERAL:
		if(a_mode && (val->val <= 0x1f)){
			return 0;
		}else{
			return 1;
		}
	case LOC_REGISTER:
	case LOC_REGISTER_MEMORY:
	case LOC_PUSHPOP: 
	case LOC_PEEK:
	case LOC_SP:
	case LOC_PC:
	case LOC_EX:
	case LOC_IA:
		return 0;
	}
	return 0;
}
