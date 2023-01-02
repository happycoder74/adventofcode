#include <glib.h>
#include <stdlib.h>
#include "aoc_grid.h"

Grid *grid_new(int rows, int columns) {
    Grid *grid = malloc(sizeof(Grid));
    grid->grid = calloc(sizeof(int),  rows * columns);
    grid->rows = rows;
    grid->columns = columns;

    return grid;
}

int grid_index(Grid *grid, int row, int column) {
    int index = row * grid->columns + column;
    return grid->grid[index];
}

void grid_index_set(Grid *grid, int row, int column, int value) {
    int index = row * grid->columns + column;
    grid->grid[index] = value;
}

