#ifndef _AOC_SETS_H_
#define _AOC_SETS_H_

#include <glib.h>

typedef enum {
    SET_INT,
    SET_CHAR,
    SET_STR,
    SET_REAL
} SetType;

typedef struct {
    GHashTable *set;
    SetType settype;
} Set;

Set *set_new_with_data(GArray *data, SetType settype);
Set *set_intersect(Set *set1, Set *set2);
Set *set_difference(Set *set1, Set *set2);
Set *set_union(Set *set1, Set *set2);

void set_free(Set *set);
int set_add(Set *set, gconstpointer v);


#endif
