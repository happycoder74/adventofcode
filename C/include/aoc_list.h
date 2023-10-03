#ifndef __AOC_LIST_H__
#define __AOC_LIST_H__

#include <stdint.h>
#include "aoc_types.h"


AocSList *aoc_slist_prepend(AocSList *, void *);
AocSList *aoc_slist_reverse(AocSList *);

#endif // !__AOC_LIST_H__
