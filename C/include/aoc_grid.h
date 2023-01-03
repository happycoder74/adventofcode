#ifndef __AOC_GRID_H__
#define __AOC_GRID_H__

typedef struct {
    int *grid;
    int rows;
    int columns;
} Grid;

Grid *grid_new(int rows, int columns);
int grid_index(Grid *grid, int row, int column);
void grid_index_set(Grid *grid, int row, int column, int value);
Grid *grid_copy(const Grid *grid);
void grid_free(Grid *grid);

#endif
