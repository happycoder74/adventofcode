#ifndef __AOC_LIST_H__
#define __AOC_LIST_H__

#include "aoc_types.h"

/**
 * aoc_slist_prepend(AocSList *list, void *data)
 *
 * add a node with data 'data' to the front of the 'list'
 */

AocSList *aoc_slist_prepend(AocSList *, void *);

/**
 * aoc_slist_reverse(AocSList *list)
 *
 * reverses list 'list'
 */
AocSList *aoc_slist_reverse(AocSList *);

/**
 * aoc_slist_append(AocSList *list, void *data)
 *
 * add a node with data 'data' to the back of the 'list'
 */
AocSList *aoc_slist_append(AocSList *, void *);

#endif // !__AOC_LIST_H__
