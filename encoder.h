#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "types.h"

void init_encoder();
unsigned short encode_op(const char *str);
unsigned short encode_val(const char *str, bool aval);

#endif
