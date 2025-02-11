#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include "intcode.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr return_array = aoc_array_new(AOC_INT32, 2000);
    char      **instructions = aoc_str_split(aoc_str_array_index(data, 0), ",", 0);
    int         opcode;

    int32_t *array_data = (int32_t *)calloc(2000, sizeof(int32_t));
    uint8_t *arr_data = (uint8_t *)*(uint64_t *)(((uint8_t *)return_array) + sizeof(size_t) * 5);
    memmove(arr_data, array_data, 2000 * sizeof(int32_t));
    // free(array_data);
    return_array->length = 2000;

    char **p = instructions;
    size_t i = 0;

    while (*p != NULL) {
        opcode = atoi(*p);
        aoc_int32_array_set_index(return_array, i++, opcode);
        p++;
    }
    aoc_str_freev(instructions);

    return return_array;
}

void *solve_part_1(AocData_t *data) {
    AocArrayPtr      instructions = aoc_array_copy(aoc_data_get(data));
    int              input_value = 1;
    IntCodeReturn_t *rv = intcode(instructions, &input_value);

    int return_value = aoc_int32_array_index(rv->return_buffer, rv->return_buffer->length - 1);

    aoc_int32_array_free(instructions);
    intcode_return_free(rv);
    return strdup_printf("%d", return_value);
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr instructions = aoc_array_copy(aoc_data_get(data));
    int         input_value = 5;

    IntCodeReturn_t *rv = intcode(instructions, &input_value);
    int return_value = aoc_int32_array_index(rv->return_buffer, rv->return_buffer->length - 1);

    aoc_int32_array_free(instructions);
    intcode_return_free(rv);
    return strdup_printf("%d", return_value);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2019;
    const unsigned day = 5;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
