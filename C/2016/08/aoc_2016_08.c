#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_grid.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum command_type {
    INIT,
    ROW,
    COL
};

typedef struct {
    enum command_type command;
    int               value1;
    int               value2;
} Instruction;

AocArrayPtr clean_input(AocArrayPtr data) {
    char        *line;
    unsigned int i;
    Instruction *instruction;
    AocArrayPtr  instruction_list;

    instruction_list = aoc_array_sized_new(AOC_ARRAY_PTR, aoc_array_length(data));

    for (i = 0; i < aoc_array_length(data); i++) {
        line = aoc_str_array_index(data, i);
        if (strstr(line, "rect")) {
            instruction = (Instruction *)malloc(sizeof(Instruction));
            instruction->command = INIT;
            sscanf(line, "rect %dx%d", &instruction->value1, &instruction->value2);
            aoc_ptr_array_append(instruction_list, instruction);
        } else if (strstr(line, "rotate col")) {
            instruction = (Instruction *)malloc(sizeof(Instruction));
            instruction->command = COL;
            sscanf(line, "rotate column x=%d by %d", &instruction->value1, &instruction->value2);
            aoc_ptr_array_append(instruction_list, instruction);
        } else if (strstr(line, "rotate row")) {
            instruction = (Instruction *)malloc(sizeof(Instruction));
            instruction->command = ROW;
            sscanf(line, "rotate row y=%d by %d", &instruction->value1, &instruction->value2);
            aoc_ptr_array_append(instruction_list, instruction);
        }
    }
    aoc_str_array_free_all(data);
    return instruction_list;
}

void init_area(Grid *grid, Instruction *instruction) {
    int row, col;
    int index;
    for (row = 0; row < instruction->value2; row++) {
        for (col = 0; col < instruction->value1; col++) {
            index = row * grid->columns + col;
            grid->grid[index] = 1;
        }
    }
    return;
}

void rotate_col(Grid *grid, Instruction *instruction) {
    int *col_to_rotate;
    int  row;
    int  i, index;

    col_to_rotate = malloc(sizeof(int) * grid->rows);
    index = instruction->value1;

    for (row = 0; row < grid->rows; row++) {
        i = (row + instruction->value2) % grid->rows;
        col_to_rotate[i] = grid->grid[row * grid->columns + index];
    }

    for (row = 0; row < grid->rows; row++) {
        grid->grid[row * grid->columns + index] = col_to_rotate[row];
    }

    free(col_to_rotate);
    return;
}

void rotate_row(Grid *grid, Instruction *instruction) {
    int *row_to_rotate;
    int  col;
    int  i, index;

    row_to_rotate = malloc(sizeof(int) * grid->columns);
    index = instruction->value1 * grid->columns;

    for (col = 0; col < grid->columns; col++) {
        i = (col + instruction->value2) % grid->columns;
        row_to_rotate[i] = grid->grid[col + index];
    }
    for (col = 0; col < grid->columns; col++) {
        grid->grid[col + index] = row_to_rotate[col];
    }

    free(row_to_rotate);
    return;
}

void grid_print(Grid *grid, int final) {
    int row, col, i;

    for (row = 0; row < grid->rows; row++) {
        for (col = 0; col < grid->columns; col++) {
            i = row * grid->columns + col;
            if (grid->grid[i] > 0) {
                printf("\u2588");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    if (!final) { /* Rewind to beginning */
        printf("\r\033[6A");
    } else {
        printf("\n");
    }
}
void *solve_part_1(AocData_t *data) {
    Grid        *grid;
    unsigned int i;
    int          row, col, index;
    Instruction *instruction;

    grid = malloc(sizeof(Grid));
    grid->rows = 6;
    grid->columns = 50;
    grid->grid = calloc((grid->rows * grid->columns), sizeof(int));

    AocArrayPtr d = aoc_data_get(data);
    for (i = 0; i < aoc_data_length(data); i++) {
        instruction = aoc_ptr_array_index(d, i);
        switch (instruction->command) {
            case INIT:
                init_area(grid, instruction);
                break;
            case COL:
                rotate_col(grid, instruction);
                break;
            case ROW:
                rotate_row(grid, instruction);
                break;
            default:
                fprintf(stderr, "Error in commands");
                exit(EXIT_FAILURE);
        }
        grid_print(grid, 0);
    }

    int count = 0;
    for (row = 0; row < grid->rows; row++) {
        for (col = 0; col < grid->columns; col++) {
            index = row * grid->columns + col;
            count += grid->grid[index];
        }
    }

    grid_print(grid, 1);

    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    return strdup("See above");
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2016;
    const unsigned day = 8;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
