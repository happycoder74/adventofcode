#ifndef _AOC_SETS_H_
#define _AOC_SETS_H_

#include "aoc_hash.h"
#include "aoc_types.h"

typedef enum {
    AOC_SET_INT32,
    AOC_SET_INT64,
    AOC_SET_UINT32,
    AOC_SET_UINT64,
    AOC_SET_CHAR,
    AOC_SET_STR,
    AOC_SET_PTR,
    AOC_SET_UCHAR,
    AOC_SET_LINE,
    AOC_SET_POINT,
    AOC_SET_COUNT
} AocSetType;

typedef struct {
    AocHashTable *set;
    AocSetType    settype;
} AocSet;

AocSet   *aoc_set_new_with_data(AocArray *data, AocSetType settype);
AocSet   *aoc_set_intersect(AocSet *set1, AocSet *set2);
AocSet   *aoc_set_difference(AocSet *set1, AocSet *set2);
AocSet   *aoc_set_union(AocSet *set1, AocSet *set2);
AocArray *aoc_set_get_values(AocSet *set);

void aoc_set_free(AocSet *set);
int  aoc_set_add(AocSet *set, const void *value);

#endif
