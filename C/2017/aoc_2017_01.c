#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr array = aoc_int32_array_new();
    char       *str = aoc_str_array_index(data, 0);

    for (size_t i = 0; i < strlen(str); i++) {
        int int_char = str[i] - '0';
        aoc_int32_array_append(array, int_char);
    }
    return array;
}

static int solver(AocArrayPtr array, int step) {
    int sum = 0;

    for (size_t i = 0; i < aoc_array_length(array); i++) {
        size_t j = (i + step) % aoc_array_length(array);
        if (aoc_int32_array_index(array, i) == aoc_int32_array_index(array, j)) {
            sum += aoc_int32_array_index(array, i);
        }
    }
    return sum;
}

void *solve_part_1(AocData_t *data) {
    return strdup_printf("%d", solver(aoc_data_get(data), 1));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%d", solver(aoc_data_get(data), aoc_data_length(data) / 2));
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2017;
    const unsigned day = 1;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);
    aoc_data_free(data);

    return aoc_mem_gc();
}
