#include "codelist_entry.h"
#include "token_val.h"
#include "codes.h"

int codelist_entry_size(codelist_entry *entry){
	int size = 0;
	switch(entry->type){
	case CODELIST_ENTRY_TYPE_OP:
		size = 1;
		size += token_val_size(entry->aval, TRUE);
		size += token_val_size(entry->bval, FALSE);
		break;
	case CODELIST_ENTRY_TYPE_SPECIAL_OP:
		size = 1;
		size += token_val_size(entry->aval, TRUE);
		break;
	case CODELIST_ENTRY_TYPE_DATA:
		size = entry->data_size;
		break;
	case CODELIST_ENTRY_TYPE_LABEL:
		size = 0;
		break;
	}
	return size;
}
