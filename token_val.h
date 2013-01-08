#ifndef _TOKEN_VAL_H_
#define _TOKEN_VAL_H_

#include "types.h"

/**
 * returns the size of a tokenval, from 0 to 1, whether it uses the next word or not
 *
 **/
int token_val_size(token_val *val, bool a_mode);

#endif
