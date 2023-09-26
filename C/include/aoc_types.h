#ifndef _AOC_TYPES_H_
#define _AOC_TYPES_H_

#include "aoc_array.h"

typedef struct {
    char *filename;
    int year;
    int day;
    AocArrayPtr data;
} AocData_t;

#endif
