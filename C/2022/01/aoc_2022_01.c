#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <glib.h>
#include "aoc_array.h"
#include "aoc_utils.h"
#include "aoc_string.h"

AocArray *clean_input(AocArray *data) {
    GArray *return_data = aoc_int_array_new();
    char *row;
    size_t i = 0;
    uint32_t elf_sum = 0;
    for (i = 0; i < aoc_array_length(data); i++) {
        row = (char *)aoc_array_index(data, i);
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
    return strdup_printf("%d", (int *)aoc_array_index(data->data, 0));
}

void *solve_part_2(AocData_t *data) {
    size_t i;
    uint32_t return_sum = 0;

    // Since array is already sorted from part 1
    // we can just return the sum of the three first
    // items.
    for(i = 0; i < 3; i++) {
        return_sum += g_array_index(data->data, int, i);
    }
    return strdup_printf("%d", return_sum);
}

void *solve_all(AocData_t *data) {

    data = aoc_data_set_data(data, clean_input(aoc_data_data(data)));

    if (data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    char *sourcefile;
    int year, day;

    sourcefile = basename(__FILE__);
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);

    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
