#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *clean_input(void *input) {
    AocArrayPtr  return_data = aoc_int32_array_new();
    AocArrayPtr  data        = (AocArrayPtr)input;
    char        *row;
    size_t       i            = 0;
    uint32_t     elf_sum      = 0;
    const size_t array_length = aoc_array_length(data);
    for (i = 0; i < array_length; i++) {
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

int solve_part_2(void *input) {
    AocData_t *data = (AocData_t *)input;
    size_t     i;
    uint32_t   return_sum = 0;

    // Since array is already sorted from part 1 we can just return the sum of the three first
    // items.
    for (i = 0; i < 3; i++) {
        return_sum += aoc_int32_array_index(aoc_data_get(data), i);
    }
    return return_sum;
}

void solve_all(void *input) {
    AocData_t  *data = (AocData_t *)input;
    AocArrayPtr parsed_data =
        (AocArrayPtr)timer_return(clean_input, data->data, "Preparation time:");
    data->data = parsed_data;

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func_new(2, solve_part_2, data, 1);
    }
}

int main(int argc, char **argv) {

    const unsigned year = 2022;
    const unsigned day  = 1;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_void(solve_all, data, "Time elapsed:");

    aoc_data_free(data);

    return aoc_mem_gc();
}
