#include "aoc_hash.h"
#include <stdlib.h>

typedef struct {
    AocHashTable *table;
    int           dimensions;
} GridH;

typedef struct {
    int *values;
    int  dimension;
} Tuple;

GridH *grid_hash_new() {
    GridH *grid = (GridH *)malloc(sizeof(GridH));

    return grid;
}

int grid_hash_get(GridH *grid, Tuple *position) {
    AocHashTable *table = grid->table;
    int          *return_value;

    return_value = (int *)aoc_hash_table_lookup(table, position);

    return *return_value;
}
