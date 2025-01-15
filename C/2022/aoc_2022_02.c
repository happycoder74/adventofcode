#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_requested(int row, int col) {
    if (row == 0) {
        switch (col) {
            case 0:
                return 2;
            case 1:
                return 0;
            case 2:
                return 1;
        }
    }
    if (row == 1) {
        return col;
    }
    if (row == 2) {
        switch (col) {
            case 0:
                return 1;
            case 1:
                return 2;
            case 2:
                return 0;
        }
    }
    return -1;
}

void *solve_part_1(AocData_t *data) {
    int shape_points[3] = {1, 2, 3};
    int col, row;
    int points[3][3] = {
        {3, 6, 0},
        {0, 3, 6},
        {6, 0, 3}
    };

    size_t i;
    char  *draw;

    int sum_points = 0;

    for (i = 0; i < aoc_data_length(data); i++) {
        draw = aoc_str_array_index(aoc_data_get(data), i);
        row = draw[0] - 'A';
        col = draw[2] - 'X';
        sum_points += points[row][col] + shape_points[col];
    }

    return strdup_printf("%d", sum_points);
}

void *solve_part_2(AocData_t *data) {
    int    shape_points[3] = {1, 2, 3};
    int    col, row;
    size_t i;
    int    sum_points = 0;
    int    points[3] = {0, 3, 6};
    char  *draw;

    for (i = 0; i < aoc_data_length(data); i++) {
        draw = aoc_str_array_index(aoc_data_get(data), i);
        row = draw[0] - 'A';
        col = draw[2] - 'X';
        sum_points += points[col] + shape_points[get_requested(row, col)];
    }

    return strdup_printf("%d", sum_points);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2022;
    const unsigned day = 2;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
