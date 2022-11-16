#ifndef _AOC_TYPES_H_
#define _AOC_TYPES_H_

#include "aoc_sets.h"

typedef struct {
    gchar *filename;
    gint year;
    gint day;
    GArray *data;
} AocData_t;

#endif
