#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>

#include "aoc_utils.h"


enum command_type {INIT, ROW, COL};

typedef struct {
    enum command_type command;
    gint value1;
    gint value2;
} Instruction;

GArray *parse_data(GArray *data) {
    gchar *line;
    guint i;
    Instruction *instruction;
    GArray *instruction_list;

    instruction_list = g_array_sized_new(FALSE, FALSE, sizeof(Instruction *), data->len);

    for (i = 0; i < data->len; i++) {
        line = g_array_index(data, gchar *, i);
        if(g_strstr_len(line, 4, "rect")) {
            instruction = g_new(Instruction, 1);
            instruction->command = INIT;
            sscanf(line, "rect %dx%d", &instruction->value1, &instruction->value2);
            g_array_append_val(instruction_list, instruction);
        } else if (g_strstr_len(line, 10, "rotate col")) {
            instruction = g_new(Instruction, 1);
            instruction->command = COL;
            sscanf(line, "rotate column x=%d by %d", &instruction->value1, &instruction->value2);
            g_array_append_val(instruction_list, instruction);
        } else if (g_strstr_len(line, 10, "rotate row")) {
            instruction = g_new(Instruction, 1);
            instruction->command = ROW;
            sscanf(line, "rotate row y=%d by %d", &instruction->value1, &instruction->value2);
            g_array_append_val(instruction_list, instruction);
        }
    }
    return instruction_list;
}

void init_area(Grid *grid, Instruction *instruction) {
    int row, col;
    int index;
    for (row = 0; row < instruction->value2; row++) {
        for (col = 0; col < instruction->value1; col++) {
            index = row*grid->columns + col;
            grid->grid[index] = 1;
        }
    }
    return;
}

void rotate_col(Grid *grid, Instruction *instruction) {
    int *col_to_rotate;
    int row;
    int i, index;

    col_to_rotate = malloc(sizeof(int) * grid->rows);
    index = instruction->value1;

    for (row = 0; row < grid->rows; row++) {
        i = (row  + instruction->value2) % grid->rows;
        col_to_rotate[i] = grid->grid[row*grid->columns + index];
    }

    for (row = 0; row < grid->rows; row++) {
        grid->grid[row*grid->columns + index] = col_to_rotate[row];
    }

    free(col_to_rotate);
    return;
}

void rotate_row(Grid *grid, Instruction *instruction) {
    int *row_to_rotate;
    int col;
    int i, index;

    row_to_rotate = malloc(sizeof(int)*grid->columns);
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
            i = row*grid->columns + col;
            printf("%s", grid->grid[i] > 0 ? "\u2593": " ");
        }
        printf("\n");
    }
    if (!final) { /* Rewind to beginning */
        printf("\r\033[6A");
    } else {
        printf("\n");
    }
}
int solve_part_1(GArray *data) {
    Grid *grid;
    guint i;
    int row, col, index;
    Instruction *instruction;

    grid = malloc(sizeof(Grid));
    grid->rows = 6;
    grid->columns = 50;
    grid->grid = calloc((grid->rows * grid->columns), sizeof(int));

    for (i = 0; i < data->len; i++) {
        instruction = g_array_index(data, Instruction *, i);
        switch(instruction->command) {
            case INIT:
                init_area(grid, instruction);
                break;
            case COL:
                rotate_col(grid, instruction);
                break;
            case ROW:
                rotate_row(grid, instruction);
                break;
        }
        grid_print(grid, 0);
        usleep(10000);
    }

    int count = 0;
    for (row = 0; row < 6; row++) {
        for (col = 0; col < 50; col++) {
            index = row*grid->columns + col;
            count += grid->grid[index];
        }
    }

    grid_print(grid, 1);

    return count;
}

char *solve_part_2() {
    return strdup("\u261D");
}


int solve_all(char *filename, int year, int day) {
    GArray *data;

    data = parse_data(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(), STR, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2016, 8), INT, 0);

    free(filename);

}
