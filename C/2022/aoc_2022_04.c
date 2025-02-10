#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_sets.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArray *clean_input(AocArray *data) {
    AocArrayPtr elves = aoc_array_new(AOC_PTR, data->length * 2);
    for (unsigned i = 0; i < data->length; i++) {
        char   *row = aoc_str_array_index(data, i);
        int32_t p0min, p0max;
        int32_t p1min, p1max;
        p0min = atoi(row);
        p0max = atoi(strchr(row, '-') + 1);
        p1min = atoi(strchr(row, ',') + 1);
        p1max = atoi(strchr(strchr(row, ',') + 1, '-') + 1);
        AocArrayPtr list = aoc_array_new(AOC_INT32, 4);
        aoc_int32_array_append(list, p0min);
        aoc_int32_array_append(list, p0max);
        aoc_int32_array_append(list, p1min);
        aoc_int32_array_append(list, p1max);

        aoc_ptr_array_append(elves, list);
    }
    aoc_str_array_free_all(data);

    return elves;
}

void *solve_part_1(AocData_t *data) {
    unsigned overlaps = 0;
    for (unsigned i = 0; i < aoc_data_length(data); i++) {
        AocArrayPtr list = aoc_ptr_array_index(data->data, i);
        int         p0min = aoc_int32_array_index(list, 0);
        int         p0max = aoc_int32_array_index(list, 1);
        int         p1min = aoc_int32_array_index(list, 2);
        int         p1max = aoc_int32_array_index(list, 3);

        if (((p0min <= p1min) && (p1max <= p0max)) || ((p1min <= p0min) && (p0max <= p1max))) {
            overlaps += 1;
        }
    }
    return strdup_printf("%d", overlaps);
}

void *solve_part_2(AocData_t *data) {
    unsigned overlaps = 0;
    for (unsigned i = 0; i < aoc_data_length(data); i++) {
        AocArrayPtr list = aoc_ptr_array_index(data->data, i);
        int         p0min = aoc_int32_array_index(list, 0);
        int         p0max = aoc_int32_array_index(list, 1);
        int         p1min = aoc_int32_array_index(list, 2);
        int         p1max = aoc_int32_array_index(list, 3);

        if (((p1min <= p0min) && (p0min <= p1max)) || ((p0min <= p1min) && (p1min <= p0max))) {
            overlaps += 1;
        }
    }
    return strdup_printf("%d", overlaps);
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
    const unsigned day = 4;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
