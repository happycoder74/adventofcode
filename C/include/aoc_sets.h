#ifndef _AOC_SETS_H_
#define _AOC_SETS_H_

#include "aoc_hash.h"
#include "aoc_types.h"

typedef AocType AocSetType;

typedef struct {
    AocHashTable *set;
    AocSetType    settype;
} AocSet;

#define aoc_set_size(_set_) (((_set_) != NULL) ? ((ssize_t)aoc_hash_table_count(_set_->set)) : (-1))

AocSet   *aoc_set_new(AocSetType settype);
AocSet   *aoc_set_new_with_data(AocArray *data, AocSetType settype);
AocSet   *aoc_set_intersect(AocSet *set1, AocSet *set2);
AocSet   *aoc_set_difference(AocSet *set1, AocSet *set2);
AocSet   *aoc_set_union(AocSet *set1, AocSet *set2);
AocArray *aoc_set_get_values(AocSet *set);

void aoc_set_free(AocSet *set);
int  aoc_set_add(AocSet *set, const void *value);

#endif
