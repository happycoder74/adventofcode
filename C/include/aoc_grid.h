#ifndef __AOC_GRID_H__
#define __AOC_GRID_H__

#include "aoc_types.h"
#include <stdbool.h>

typedef struct {
    void **grid;
    size_t rows;
    size_t columns;
    int    max_row;
    int    min_row;
    int    max_column;
    int    min_column;
} AocGrid;

typedef struct {
    unsigned rows;
    unsigned columns;
} GridDimensions;

AocGrid *aoc_grid_new(GridDimensions *dimensions);
bool     aoc_grid_set(AocGrid *grid, int row, int column, void *value);
bool     aoc_grid_replace(AocGrid *grid, int row, int column, void *value);
void     aoc_grid_free(AocGrid *grid);
void    *aoc_grid_get(AocGrid *grid, int row, int column);
void     aoc_grid_rotate_row(AocGrid *grid, int32_t row, int32_t rotate_columns);
void     aoc_grid_rotate_column(AocGrid *grid, int32_t col, int32_t rotate_rows);
void     aoc_grid_delete(AocGrid *grid, int32_t row, int32_t col);
uint32_t aoc_grid_elements(AocGrid *grid);

AocArrayPtr aoc_grid_row(AocGrid *grid, int row);
AocArrayPtr aoc_grid_column(AocGrid *grid, int column);

/* AocGrid *aoc_grid_copy(const AocGrid *grid); */

#endif
