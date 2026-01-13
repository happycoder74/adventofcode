#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr array = aoc_int32_array_new();

    for (size_t i = 0; i < aoc_array_length(data); i++) {
        int32_t value = atoi(aoc_str_array_index(data, i));
        aoc_int32_array_append(array, value);
    }
    return array;
}

int32_t solve_part_1(AocData_t *data) {
    int32_t sum = 0;

    AocArrayPtr arr = aoc_data_get(data);

    for (size_t i = 0; i < aoc_data_length(data); i++) {
        sum += aoc_int32_array_index(arr, i);
    }
    return sum;
}

int32_t solve_part_2(AocData_t *data) {
    AocHashTablePtr ht        = aoc_hash_table_create(AOC_PTR);
    int32_t         frequency = 0;
    AocArrayPtr     arr       = aoc_data_get(data);

    aoc_hash_table_add(ht, (void *)(int64_t)frequency);
    while (true) {
        for (size_t i = 0; i < aoc_data_length(data); ++i) {
            frequency += aoc_int32_array_index(arr, i);
            if (aoc_hash_table_contains(ht, (void *)(int64_t)frequency)) {
                return frequency;
            }
            aoc_hash_table_add(ht, (void *)(int64_t)frequency);
        }
    }
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func_int(1, solve_part_1, data, 1);
        timer_func_int(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2018;
    const unsigned day  = 1;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);
    aoc_data_free(data);

    return aoc_mem_gc();
}
