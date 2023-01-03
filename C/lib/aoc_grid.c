#include <stdlib.h>
#include <string.h>
#include "aoc_grid.h"

Grid *grid_new(int rows, int columns) {
    Grid *grid = (Grid *)malloc(sizeof(Grid));
    grid->grid = (int *)calloc(sizeof(int), rows * columns);
    grid->rows = rows;
    grid->columns = columns;

    return grid;
}

void grid_free(Grid *grid) {
    g_free(grid->grid);
    g_free(grid);
}

Grid *grid_copy(const Grid *grid) {
    Grid *grid_copy = (Grid *)malloc(sizeof(Grid));
    grid_copy->rows = grid->rows;
    grid_copy->columns = grid->columns;
    grid_copy->grid = (int *)calloc(sizeof(int), grid->rows * grid->columns);
    grid_copy->grid = (int *)memcpy(grid_copy->grid, grid->grid, (size_t)(sizeof(int)*(grid->rows * grid->columns)));
    return grid_copy;
}

int grid_index(Grid *grid, int row, int column) {
    int index = row * grid->columns + column;
    return grid->grid[index];
}

void grid_index_set(Grid *grid, int row, int column, int value) {
    int index = row * grid->columns + column;
    grid->grid[index] = value;
}
