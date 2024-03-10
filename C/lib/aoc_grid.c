#include "aoc_grid.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

AocGrid *aoc_grid_new(GridDimensions *dimensions) {
    AocGrid *grid = (AocGrid *)malloc(sizeof(AocGrid));
    grid->grid = aoc_hash_table_create(AOC_POINT);
    grid->rows = 0;
    grid->columns = 0;
    if (dimensions) {
        grid->rows = dimensions->rows;
        grid->columns = dimensions->columns;
    }
    grid->min_row = 0;
    grid->max_row = MAX(0, (int)grid->rows - 1);
    grid->min_column = 0;
    grid->max_column = MAX(0, (int)grid->columns - 1);
    return grid;
}

void aoc_grid_free(AocGrid *grid) {
    aoc_hash_table_destroy(&grid->grid);
}

/* Grid *grid_copy(const Grid *grid) { */
/*     Grid *grid_copy = (Grid *)malloc(sizeof(Grid)); */
/*     grid_copy->rows = grid->rows; */
/*     grid_copy->columns = grid->columns; */
/*     grid_copy->grid = (int *)calloc(sizeof(int), grid->rows * grid->columns); */
/*     grid_copy->grid = (int *)memcpy(grid_copy->grid, grid->grid, */
/*                                     (size_t)(sizeof(int) * (grid->rows * grid->columns))); */
/*     return grid_copy; */
/* } */

bool aoc_grid_set(AocGrid *grid, int row, int column, void *value) {
    Point *key = point_new_m(row, column);
    grid->min_row = MIN(grid->min_row, row);
    grid->max_row = MAX(grid->max_row, row);
    grid->min_column = MIN(grid->min_column, column);
    grid->max_column = MAX(grid->max_column, column);
    grid->rows = grid->max_row - grid->min_row + 1;
    grid->columns = grid->max_column - grid->min_column + 1;

    return aoc_hash_table_insert(grid->grid, key, value);
}

bool aoc_grid_replace(AocGrid *grid, int row, int column, void *value) {
    Point key = {row, column};
    return aoc_hash_table_replace(grid->grid, &key, value);
}

void *aoc_grid_get(AocGrid *grid, int row, int column) {
    Point p = {row, column};
    return aoc_hash_table_lookup(grid->grid, &p);
}

AocArrayPtr aoc_grid_row(AocGrid *grid, int row) {
    AocArrayPtr grid_row = aoc_array_new(AOC_PTR, grid->rows);
    for (int i = grid->min_column; i <= grid->max_column; i++) {
        Point p = {row, i};
        void *value = aoc_hash_table_lookup(grid->grid, &p);
        aoc_ptr_array_append(grid_row, value);
    }

    return grid_row;
}

AocArrayPtr aoc_grid_column(AocGrid *grid, int column) {
    AocArrayPtr grid_column = aoc_array_new(AOC_PTR, grid->columns);
    for (int i = grid->min_row; i <= grid->max_row; i++) {
        Point p = {i, column};
        void *value = aoc_hash_table_lookup(grid->grid, &p);
        aoc_ptr_array_append(grid_column, value);
    }

    return grid_column;
}

uint32_t aoc_grid_elements(AocGrid *grid) {
    return aoc_hash_table_count(grid->grid);
}

void aoc_grid_delete(AocGrid *grid, int32_t row, int32_t col) {
    Point p = {row, col};
    aoc_hash_table_delete(grid->grid, &p);
}

void aoc_grid_rotate_row(AocGrid *grid, int32_t row, int32_t rotate_cols) {
    void **new_row = malloc(sizeof(void *) * grid->columns);
    for (int col = grid->min_column; col <= grid->max_column; col++) {
        int32_t index = (col + rotate_cols) % grid->columns;
        new_row[index] = aoc_grid_get(grid, row, col);
    }
    for (int col = grid->min_column; col <= grid->max_column; col++) {
        /* aoc_grid_replace(grid, row, col, new_row[col]); */
        aoc_grid_delete(grid, row, col);
        aoc_grid_set(grid, row, col, new_row[col]);
    }
}

void aoc_grid_rotate_column(AocGrid *grid, int32_t col, int32_t rotate_rows) {
    void **new_column = malloc(sizeof(void *) * grid->rows);
    for (int row = grid->min_row; row <= grid->max_row; row++) {
        int32_t index = (row + rotate_rows) % grid->rows;
        new_column[index] = aoc_grid_get(grid, row, col);
    }
    for (int row = grid->min_row; row <= grid->max_row; row++) {
        aoc_grid_delete(grid, row, col);
        aoc_grid_set(grid, row, col, new_column[row]);
    }
}
