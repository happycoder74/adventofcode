#include "aoc_grid.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocGrid *aoc_grid_new(GridDimensions *dimensions) {
    AocGrid *grid = (AocGrid *)malloc(sizeof(AocGrid));
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
    grid->grid = calloc(grid->rows * grid->columns, sizeof(void *));
    return grid;
}

void aoc_grid_free(AocGrid *grid) {
    free(grid->grid);
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
    grid->min_row = MIN(grid->min_row, row);
    grid->max_row = MAX(grid->max_row, row);
    grid->min_column = MIN(grid->min_column, column);
    grid->max_column = MAX(grid->max_column, column);
    grid->rows = grid->max_row - grid->min_row + 1;
    grid->columns = grid->max_column - grid->min_column + 1;

    unsigned index = row * grid->columns + column;
    bool     existed = grid->grid[index] != NULL;
    grid->grid[index] = value;
    return existed;
}

bool aoc_grid_replace(AocGrid *grid, int row, int column, void *value) {
    unsigned index = row * grid->columns + column;
    bool     existed = grid->grid[index] == NULL;
    grid->grid[index] = value;
    return existed;
}

void *aoc_grid_get(AocGrid *grid, int row, int column) {
    unsigned index = row * grid->columns + column;
    return grid->grid[index];
}

AocArrayPtr aoc_grid_row(AocGrid *grid, int row) {
    AocArrayPtr grid_row = aoc_array_new(AOC_PTR, grid->columns);
    for (int i = grid->min_column; i <= grid->max_column; i++) {
        unsigned index = row * grid->columns + i;
        void    *value = grid->grid[index];
        aoc_ptr_array_append(grid_row, value);
    }

    return grid_row;
}

AocArrayPtr aoc_grid_column(AocGrid *grid, int column) {
    AocArrayPtr grid_column = aoc_array_new(AOC_PTR, grid->rows);
    for (int i = grid->min_row; i <= grid->max_row; i++) {
        unsigned index = i * grid->columns + column;
        void    *value = grid->grid[index];
        aoc_ptr_array_append(grid_column, value);
    }

    return grid_column;
}

uint32_t aoc_grid_elements(AocGrid *grid) {
    unsigned count = 0;
    for (unsigned index = 0; index < grid->rows * grid->columns; index++) {
        if (grid->grid[index]) {
            count++;
        }
    }
    return count;
}

void aoc_grid_delete(AocGrid *grid, int32_t row, int32_t col) {
    grid->grid[row * grid->columns + col] = NULL;
}

void aoc_grid_rotate_row(AocGrid *grid, int32_t row, int32_t rotate_cols) {
    void   **new_row = calloc(grid->columns, sizeof(void *));
    unsigned index = row * grid->columns;
    memmove(new_row + rotate_cols, grid->grid + index,
            (grid->columns - rotate_cols) * sizeof(void *));
    memmove(new_row, grid->grid + index + grid->columns - rotate_cols,
            rotate_cols * sizeof(void *));

    memmove(grid->grid + index, new_row, grid->columns * sizeof(void *));
    free(new_row);
}

void aoc_grid_rotate_column(AocGrid *grid, int32_t col, int32_t rotate_rows) {
    void **column = calloc(grid->rows, sizeof(void *));
    void **new_column = calloc(grid->rows, sizeof(void *));
    for (int row = grid->min_row; row <= grid->max_row; row++) {
        int32_t index = row * grid->columns + col;
        column[row] = grid->grid[index];
    }
    memmove(new_column + rotate_rows, column, (grid->rows - rotate_rows) * sizeof(void *));
    memmove(new_column, column + grid->rows - rotate_rows, rotate_rows * sizeof(void *));

    for (unsigned index = 0; index < grid->rows; index++) {
        grid->grid[index * grid->columns + col] = new_column[index];
    }
    /* free(column); */
    /* free(new_column); */
}
