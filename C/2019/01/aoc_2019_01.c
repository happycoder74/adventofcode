#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_array.h"
#include "aoc_timer.h"

int fuel_cost(int fuel) {
    fuel = (fuel / 3) - 2;
    if (fuel < 0) {
        return 0;
    } else {
        return fuel + fuel_cost(fuel);
    }
}

AocArrayPtr clean_data(AocArrayPtr data) {
    AocArrayPtr return_data = aoc_int32_array_new();
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
    int val;

    for (i = 0; i < aoc_data_length(data); i++) {
        val = aoc_int32_array_index(aoc_data_get(data), i);
        fuel += (val / 3) - 2;
    }
    return strdup_printf("%d", fuel);
}

void *solve_part_2(AocData_t *data) {
    unsigned int i;
    int val;
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
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, clean_data);
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_data);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
