#include <glib.h>
#include <stdlib.h>

typedef struct {
    GHashTable *table;
    int dimensions; 
} GridH;

typedef struct {
    int *values;
    int dimension;
} Tuple;

GridH *grid_hash_new() {
    GridH *grid = (GridH *)malloc(sizeof(GridH));

    return grid;
}

int grid_hash_get(GridH *grid, Tuple *position) {
    GHashTable *table = grid->table;
    int *return_value;

    return_value = (int *)g_hash_table_lookup(table, position);

    return *return_value;
}


