#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "aoc_array.h"
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"

AocArray *clean_input(AocArray *data) {
    AocArrayPtr return_data = aoc_array_new(sizeof(int));
    char *row;
    size_t i = 0;
    uint32_t elf_sum = 0;
    for (i = 0; i < aoc_array_length(data); i++) {
        row = aoc_str_array_index(data, i);
        if (strlen(row) > 0) {
            elf_sum += strtoul(row, NULL, 0);
        } else {
            aoc_int_array_append(return_data, elf_sum);
            elf_sum = 0;
        }
    }
    if (elf_sum != 0)
        aoc_int_array_append(return_data, elf_sum);

    aoc_array_free(data);
    return return_data;
}

int sort_int_desc(const void *a, const void *b) {
    int *_a = (int *)a;
    int *_b = (int *)b;
    return (*_b) - (*_a);
}

void *solve_part_1(AocData_t *data) {
    g_array_sort(data->data, sort_int_desc);
    return strdup_printf("%d", aoc_int_array_index(aoc_data_get(data), 0));
}

void *solve_part_2(AocData_t *data) {
    size_t i;
    uint32_t return_sum = 0;

    // Since array is already sorted from part 1
    // we can just return the sum of the three first
    // items.
    for(i = 0; i < 3; i++) {
        return_sum += aoc_int_array_index(aoc_data_get(data), 0);
    }
    return strdup_printf("%d", return_sum);
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
