#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_array.h"
#include "aoc_string.h"

int find_min(AocArrayPtr array) {
    int min;
    unsigned int i;

    min = aoc_int_array_index(array, 0);
    for (i = 1; i < array->len; i++) {
        min = MIN(min, aoc_int_array_index(array, i));
    }
    return min;
}

int find_max(AocArrayPtr array) {
    int max;
    unsigned int i;

    max = aoc_int_array_index(array, 0);
    for (i = 1; i < array->len; i++) {
        max = MAX(max, aoc_int_array_index(array, i));
    }
    return max;
}

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr result;
    char **split_line;
    char *line;
    line = aoc_str_array_index(data, 0);
    split_line = aoc_str_split(line, ",", -1);
    int i, value;

    result = aoc_array_new(sizeof(int));

    i = 0;
    while (split_line[i] != NULL) {
        sscanf(split_line[i], "%d", &value);
        aoc_int_array_append(result, value);
        i++;
    }

    aoc_str_freev(split_line);
    return result;
}

int calc_fuel(AocArrayPtr data, int position, int part) {
    if (part == 1) {
        int sum = 0;
        for (unsigned int i = 0; i < data->len; i++) {
            sum += abs(aoc_int_array_index(data, i) - position);
        }
        return sum;
    } else {
        int sum = 0;
        for (unsigned int i = 0; i < data->len; i++) {
            int d = abs(aoc_int_array_index(data, i) - position);
            for (int j = 0; j <= d; j++) {
                sum += j;
            }
        }
        return sum;
    }
}

void *solve_part_1(AocData_t *data) {
    int min_fuel, fuel, pos;

    min_fuel = calc_fuel(aoc_data_get(data), find_min(aoc_data_get(data)), 1);

    for (size_t i = 0; i < aoc_data_length(data); i ++) {
        pos = aoc_int_array_index(aoc_data_get(data), i);
        fuel = calc_fuel(aoc_data_get(data), pos, 1);
        if (fuel < min_fuel) {
            min_fuel = fuel;
        }
    }
    return strdup_printf("%d", min_fuel);
}

void *solve_part_2(AocData_t *data) {
    int min_fuel, fuel;

    min_fuel = calc_fuel(aoc_data_get(data), find_min(aoc_data_get(data)), 2);

    for (unsigned int i = 0; i < (unsigned int)find_max(aoc_data_get(data)); i++) {
        fuel = calc_fuel(aoc_data_get(data), i, 2);
        if (fuel < min_fuel) {
            min_fuel = fuel;
        }
    }
    return strdup_printf("%d", min_fuel);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    } return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, clean_input);
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
