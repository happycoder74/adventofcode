#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr lines = aoc_ptr_array_new();

    for (unsigned i = 0; i < data->length; i++) {
        char       *dataline = aoc_ptr_array_index(data, i);
        AocArrayPtr line = aoc_int32_array_new();
        char      **data_split = str_split(dataline, "\t", 0);
        for (unsigned j = 0; data_split[j] != NULL; j++) {
            int32_t value = atoi(data_split[j]);
            aoc_int32_array_append(line, value);
        }
        aoc_ptr_array_append(lines, line);
    }
    aoc_str_array_free(data);
    return lines;
}

void *solve_part_1(AocData_t *data) {
    AocArrayPtr lines = aoc_data_get(data);
    int32_t     checksum = 0;

    for (unsigned index = 0; index < lines->length; index++) {
        unsigned    min_value = INT32_MAX;
        unsigned    max_value = 0;
        AocArrayPtr line = aoc_ptr_array_index(lines, index);
        for (unsigned c = 0; c < line->length; c++) {
            int32_t value = aoc_int32_array_index(line, c);
            min_value = value < min_value ? value : min_value;
            max_value = value > max_value ? value : max_value;
        }
        checksum += max_value - min_value;
    }
    return strdup_printf("%d", checksum);
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr lines = aoc_data_get(data);
    int32_t     checksum = 0;

    for (unsigned index = 0; index < lines->length; index++) {
        AocArrayPtr line = aoc_ptr_array_index(lines, index);
        for (unsigned num1 = 0; num1 < line->length; num1++) {
            int32_t n1 = aoc_int32_array_index(line, num1);
            for (unsigned num2 = 0; num2 < line->length; num2++) {
                int32_t n2 = aoc_int32_array_index(line, num2);
                if ((n1 != n2) && ((n1 % n2) == 0)) {
                    checksum += n1 / n2;
                }
            }
        }
    }

    return strdup_printf("%d", checksum);
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
    const unsigned day = 2;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
