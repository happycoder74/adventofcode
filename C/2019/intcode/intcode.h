#ifndef __INTCODE_H__
#define __INTCODE_H__

#include "aoc_types.h"
typedef struct {
    int         return_value;
    AocArrayPtr return_buffer;
} IntCodeReturn_t;

typedef struct {
    size_t   size;
    int32_t *input;
} IntCodeInput_t;

IntCodeReturn_t *intcode(AocArrayPtr instructions, int *input);
void             intcode_return_free(IntCodeReturn_t *rv);

#endif // !__INTCODE_H__
