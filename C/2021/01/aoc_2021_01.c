#include <stdio.h>
#include <stdlib.h>
#include "aoc_array.h"
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"

void *solve_part_1(AocData_t *data) {
    size_t i;
    int count = 0;
    char *val1, *val2;
    AocArrayPtr arr = aoc_data_get(data);

    for (i = 1; i < aoc_data_length(data); i++) {
        val1 = aoc_str_array_index(arr, i - 1);
        val2 = aoc_str_array_index(arr, i);
        if (atoi(val2) > atoi(val1)) {
            count ++;
        }
    }

    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    size_t i;
    int count = 0;
    char *val1, *val2;

    AocArrayPtr arr = aoc_data_get(data);

    for (i = 3; i < aoc_data_length(data); i++) {
        val1 = aoc_str_array_index(arr, i - 3);
        val2 = aoc_str_array_index(arr, i);
        if (atoi(val2) > atoi(val1)) {
            count ++;
        }
    }

    return strdup_printf("%d", count);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
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
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new("test_input.txt", year, day);
        } else {
            data = aoc_data_new(argv[1], year, day);
        }
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}

