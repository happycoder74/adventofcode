#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include "aoc_string.h"

GArray *clean_input(GArray *data) {
    return data;
}

int get_requested(int row, int col) {
    if (row == 0)
        switch(col) {
            case 0:
                return 2;
            case 1:
                return 0;
            case 2:
                return 1;
        }
    if (row == 1)
        return col;
    if (row == 2)
        switch(col) {
            case 0:
                return 1;
            case 1:
                return 2;
            case 2:
                return 0;
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

    unsigned int i;
    char *draw;

    int sum_points = 0;

    for (i = 0; i < data->data->len; i++) {
        draw = g_array_index(data->data, gchar *, i);
        row = draw[0] - 'A';
        col = draw[2] - 'X';
        sum_points += points[row][col] + shape_points[col];
    }

    return strdup_printf("%d", sum_points);
}

void *solve_part_2(AocData_t *data) {
    int shape_points[3] = {1, 2, 3};
    int col, row;
    unsigned int i;
    int sum_points = 0;
    int points[3] = {0, 3, 6};
    char *draw;

    for (i = 0; i < data->data->len; i++) {
        draw = g_array_index(data->data, char *, i);
        row = draw[0] - 'A';
        col = draw[2] - 'X';
        sum_points += points[col] + shape_points[get_requested(row, col)];
    }

    return strdup_printf("%d", sum_points);
}

void *solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, 2022, 2);
    free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
