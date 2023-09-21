#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"

void *solve_part_1(AocData_t *data) {
    size_t i;
    char *row;
    int l, w, h;
    int area = 0;

    for (i = 0; i < data->data->len; i++) {
        row = g_array_index(data->data, char *, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        area += 2*l*w + 2*w*h + 2*h*l + MIN(MIN(l*w, w*h), h*l);
    }
    return strdup_printf("%d", area);
}

void *solve_part_2(AocData_t *data) {
    size_t i;
    char *row;
    int l, w, h;
    int ribbon = 0;

    for (i = 0; i < data->data->len; i++) {
        row = g_array_index(data->data, char *, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        ribbon += MIN(MIN(2*w + 2*l, 2*w + 2*h), 2*h + 2*l) + l*w*h;
    }
    return strdup_printf("%d", ribbon);
}

void *solve_all(AocData_t *data) {
    data->data = get_input(data->filename, data->year, data->day);

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    char *sourcefile;
    int year, day;

    sourcefile = basename(__FILE__);
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);

    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
