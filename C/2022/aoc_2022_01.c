#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArray *clean_input(AocArray *data) {
    AocArrayPtr return_data = aoc_int32_array_new();
    char       *row;
    size_t      i = 0;
    uint32_t    elf_sum = 0;
    for (i = 0; i < aoc_array_length(data); i++) {
        row = aoc_str_array_index(data, i);
        if (strlen(row) > 0) {
            elf_sum += strtoul(row, NULL, 0);
        } else {
            aoc_int32_array_append(return_data, elf_sum);
            elf_sum = 0;
        }
    }
    if (elf_sum != 0)
        aoc_int32_array_append(return_data, elf_sum);

    aoc_array_free(data, 1);
    return return_data;
}

int sort_int_desc(const void *a, const void *b) {
    int *_a = (int *)a;
    int *_b = (int *)b;
    return (*_b) - (*_a);
}

void *solve_part_1(AocData_t *data) {
    aoc_int32_array_sort(aoc_data_get(data), sort_int_desc);
    return strdup_printf("%d", aoc_int32_array_index(aoc_data_get(data), 0));
}

void *solve_part_2(AocData_t *data) {
    size_t   i;
    uint32_t return_sum = 0;

    // Since array is already sorted from part 1
    // we can just return the sum of the three first
    // items.
    for (i = 0; i < 3; i++) {
        return_sum += aoc_int32_array_index(aoc_data_get(data), 0);
    }
    return strdup_printf("%d", return_sum);
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
    const unsigned day = 1;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
