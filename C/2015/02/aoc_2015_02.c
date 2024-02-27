#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *solve_part_1(AocData_t *data) {
    size_t i;
    char  *row;
    int    l, w, h;
    int    area = 0;

    for (i = 0; i < aoc_data_length(data); i++) {
        row = (char *)aoc_ptr_array_index(data->data, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        area += 2 * l * w + 2 * w * h + 2 * h * l + MIN(MIN(l * w, w * h), h * l);
    }
    return strdup_printf("%d", area);
}

void *solve_part_2(AocData_t *data) {
    size_t i;
    char  *row;
    int    l, w, h;
    int    ribbon = 0;

    for (i = 0; i < aoc_data_length(data); i++) {
        row = (char *)aoc_ptr_array_index(data->data, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        ribbon += MIN(MIN(2 * w + 2 * l, 2 * w + 2 * h), 2 * h + 2 * l) + l * w * h;
    }
    return strdup_printf("%d", ribbon);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2015;
    const unsigned day = 2;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
