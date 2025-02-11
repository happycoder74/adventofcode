#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    char       *line;
    AocArrayPtr bitfields;
    size_t      i, j, len;

    bitfields = aoc_array_new(AOC_PTR, aoc_array_length(data));

    for (i = 0; i < aoc_array_length(data); i++) {
        line = aoc_str_array_index(data, i);
        len = strlen(line);
        AocArrayPtr bitfield = aoc_int32_array_new();
        for (j = 0; j < len; j++) {
            int32_t line_digit = line[j] - '0';
            aoc_int32_array_append(bitfield, line_digit);
        }
        aoc_ptr_array_append(bitfields, bitfield);
    }
    aoc_str_array_free(data);
    return bitfields;
}

int common_value(AocArrayPtr data, int position, int method) {
    int         sum = 0;
    AocArrayPtr bitfield;
    double      check;
    size_t      i;

    for (i = 0; i < aoc_array_length(data); i++) {
        bitfield = aoc_ptr_array_index(data, i);
        sum += aoc_int_array_index(bitfield, position);
    }
    check = (double)sum / aoc_array_length(data);
    if (method == 1) { // 1 = most, 0 = least
        return check < 0.5;
    } else {
        return check >= 0.5;
    }
}

AocArrayPtr reduce(AocArrayPtr data, int value, int position) {
    AocArrayPtr reduced;
    AocArrayPtr item;
    size_t      i;

    reduced = aoc_ptr_array_new();
    for (i = 0; i < aoc_array_length(data); i++) {
        item = aoc_ptr_array_index(data, i);
        if (aoc_int_array_index(item, position) != value) {
            aoc_ptr_array_append(reduced, item);
        }
    }
    return reduced;
}

void print_bitfield(AocArrayPtr bitfield) {
    size_t i;
    for (i = 0; i < aoc_array_length(bitfield); i++) {
        int val = aoc_int_array_index(bitfield, i);
        printf("%d ", val);
    }
    printf("\n");
}

void print_bitfields_all(AocArrayPtr bitfields) {
    size_t i;
    for (i = 0; i < aoc_array_length(bitfields); i++) {
        print_bitfield(aoc_ptr_array_index(bitfields, i));
    }
}

void *solve_part_1(AocData_t *data) {
    AocArrayPtr digits;
    uint32_t    gamma_rate, epsilon_rate;
    AocArrayPtr bitfield = aoc_ptr_array_index(aoc_data_get(data), 0);
    digits = aoc_int32_array_new();
    size_t count, i, j;

    for (j = 0; j < aoc_array_length(bitfield); j++) {
        count = 0;
        for (i = 0; i < aoc_data_length(data); i++) {
            bitfield = aoc_ptr_array_index(aoc_data_get(data), i);
            count += aoc_int32_array_index(bitfield, j);
        }
        int value = (2 * count / aoc_data_length(data) >= 1);
        aoc_int32_array_append(digits, value);
    }

    gamma_rate = 0;
    for (i = 0; i < aoc_array_length(digits); i++) {
        int j = aoc_array_length(digits) - 1 - i;
        gamma_rate += aoc_int_array_index(digits, i) * pow(2, j);
    }

    epsilon_rate = gamma_rate ^ ((int)pow(2, aoc_array_length(bitfield)) - 1);
    aoc_int32_array_free(digits);
    return strdup_printf("%d", gamma_rate * epsilon_rate);
}

int bitfield_sum(AocArrayPtr bitfield) {
    int    value = 0;
    size_t i;

    for (i = 0; i < aoc_array_length(bitfield); i++) {
        int j = aoc_array_length(bitfield) - 1 - i;
        int val = aoc_int_array_index(bitfield, i);
        value += val * (int)pow(2, j);
    }

    return value;
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr bitfield;
    AocArrayPtr oxygen_generator = NULL;
    AocArrayPtr co2_scrubber = NULL;
    AocArrayPtr og_tmp = NULL;
    AocArrayPtr co2s_tmp = NULL;

    bitfield = aoc_ptr_array_index(aoc_data_get(data), 0);

    int    oxygen_generator_value;
    int    co2_scrubber_value;
    int    value;
    size_t j;

    size_t digits = aoc_array_length(bitfield);
    for (j = 0; j < digits; j++) {
        if (j == 0) {
            value = common_value(aoc_data_get(data), j, 1);
            oxygen_generator = reduce(aoc_data_get(data), value, j);
            co2_scrubber = reduce(aoc_data_get(data), !value, j);
        } else {
            if (aoc_array_length(oxygen_generator) > 1) {
                value = common_value(oxygen_generator, j, 1);
                og_tmp = reduce(oxygen_generator, value, j);
                aoc_array_free(oxygen_generator, 0);
                oxygen_generator = og_tmp;
            }
            if (aoc_array_length(co2_scrubber) > 1) {
                value = common_value(co2_scrubber, j, 0);
                co2s_tmp = reduce(co2_scrubber, value, j);
                aoc_array_free(co2_scrubber, 0);
                co2_scrubber = co2s_tmp;
            }
        }
    }
    oxygen_generator_value = bitfield_sum(aoc_ptr_array_index(oxygen_generator, 0));
    co2_scrubber_value = bitfield_sum(aoc_ptr_array_index(co2_scrubber, 0));
    aoc_array_free(co2_scrubber, 0);
    aoc_array_free(oxygen_generator, 0);

    return strdup_printf("%d", oxygen_generator_value * co2_scrubber_value);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2021;
    const unsigned day = 3;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    for (unsigned i = 0; i < data->data->length; i++) {
        AocArrayPtr arr = aoc_array_index(data->data, i);
        aoc_array_free(arr, arr->free_segments);
    }
    data->data->free_segments = 0;
    aoc_data_free(data);

    return aoc_mem_gc();
}
