#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fuel_cost(int fuel) {
    fuel = (fuel / 3) - 2;
    if (fuel < 0) {
        return 0;
    } else {
        return fuel + fuel_cost(fuel);
    }
}

AocArrayPtr clean_data(AocArrayPtr data) {
    AocArrayPtr  return_data = aoc_int32_array_new();
    unsigned int i;
    unsigned int val;

    for (i = 0; i < aoc_array_length(data); i++) {
        val = atoi(aoc_str_array_index(data, i));
        aoc_int32_array_append(return_data, val);
    }
    return return_data;
}

void *solve_part_1(AocData_t *data) {
    unsigned int i;
    unsigned int fuel = 0;
    int          val;

    for (i = 0; i < aoc_data_length(data); i++) {
        val = aoc_int32_array_index(aoc_data_get(data), i);
        fuel += (val / 3) - 2;
    }
    return strdup_printf("%d", fuel);
}

void *solve_part_2(AocData_t *data) {
    unsigned int i;
    int          val;
    unsigned int fuel = 0;
    unsigned int sum_fuel = 0;

    for (i = 0; i < aoc_data_length(data); i++) {
        val = aoc_int32_array_index(aoc_data_get(data), i);
        fuel = (val / 3) - 2;
        sum_fuel += fuel + fuel_cost(fuel);
    }
    return strdup_printf("%d", sum_fuel);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2019;
    const unsigned day = 1;

    AocData_t *data = get_data(argc, argv, year, day, clean_data);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
