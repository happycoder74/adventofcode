#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_grid.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <locale.h>
#include <stdint.h>
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

    instruction_list = aoc_array_sized_new(AOC_PTR, aoc_array_length(data));

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

void init_area(AocGrid *grid, Instruction *instruction) {
    int row, col;
    for (row = 0; row < instruction->value2; row++) {
        for (col = 0; col < instruction->value1; col++) {
            int32_t *val = malloc(sizeof(int32_t));
            *val = 1;
            aoc_grid_set(grid, row, col, val);
        }
    }
    return;
}

void rotate_col(AocGrid *grid, Instruction *instruction) {
    aoc_grid_rotate_column(grid, instruction->value1, instruction->value2);
    return;
}

void rotate_row(AocGrid *grid, Instruction *instruction) {
    aoc_grid_rotate_row(grid, instruction->value1, instruction->value2);
    return;
}

void grid_print(AocGrid *grid, int final) {
    int row, col;

    for (row = 0; row < (int)grid->rows; row++) {
        for (col = 0; col < (int)grid->columns; col++) {
            int32_t *val = (int32_t *)aoc_grid_get(grid, row, col);
            if ((val != NULL) && (*val > 0)) {
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
    AocGrid     *grid;
    unsigned int i;
    int          row, col;
    Instruction *instruction;

    GridDimensions dimensions = {.rows = 6, .columns = 50};

    grid = aoc_grid_new(&dimensions);

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
        /* grid_print(grid, 0); */
    }

    int count = 0;
    for (row = 0; row < (int)grid->rows; row++) {
        for (col = 0; col < (int)grid->columns; col++) {
            int32_t *val = (int *)aoc_grid_get(grid, row, col);
            count += (val == NULL ? 0 : *val);
        }
    }

    grid_print(grid, 1);

    return strdup_printf("%d", aoc_grid_elements(grid));
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

    AocTimer_t *timer = aoc_timer_new();

    aoc_timer_start(timer);
    AocData_t *data = get_data(argc, argv, year, day, clean_input);
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func(0, solve_all, data, 0);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    aoc_data_free(data);

    return aoc_mem_gc();
}
