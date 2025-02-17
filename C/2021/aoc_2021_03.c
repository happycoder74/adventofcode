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

static uint8_t highest_bit_set = 0;
AocArrayPtr    clean_input(AocArrayPtr data) {
    char       *line;
    AocArrayPtr bitfields;
    size_t      i, j, len;

    bitfields = aoc_array_new(AOC_UINT32, aoc_array_length(data));

    for (i = 0; i < aoc_array_length(data); i++) {
        line = aoc_str_array_index(data, i);
        len = strlen(line);
        uint32_t val = 0;
        for (j = 0; j < len; j++) {
            int p = len - 1 - j;
            val = val | (line[j] - '0') << p;
        }
        aoc_uint32_array_append(bitfields, val);
    }
    highest_bit_set = strlen(line) - 1;
    aoc_str_array_free(data);
    return bitfields;
}

uint8_t common_value(AocArrayPtr data, int position, int method) {
    int      sum = 0;
    uint32_t bitfield;
    uint8_t  check;
    size_t   i;

    for (i = 0; i < aoc_array_length(data); i++) {
        bitfield = aoc_uint32_array_index(data, i);
        sum += ((bitfield & (1 << position)) > 0);
    }
    check = 2 * sum / aoc_array_length(data);
    if (method == 1) { // 1 = most, 0 = least
        return check < 1;
    } else {
        return check >= 1;
    }
}

AocArrayPtr reduce(AocArrayPtr data, int value, int position) {
    AocArrayPtr reduced;
    uint32_t    bitfield;
    size_t      i;

    reduced = aoc_uint32_array_new();
    for (i = 0; i < aoc_array_length(data); i++) {
        bitfield = aoc_uint32_array_index(data, i);
        if (((bitfield >> position) & 1) != value)
            aoc_uint32_array_append(reduced, bitfield);
    }
    return reduced;
}

void *solve_part_1(AocData_t *data) {
    uint32_t    gamma_rate = 0;
    uint32_t    epsilon_rate = 0;
    uint32_t    bitfield = 0;
    size_t      length = aoc_data_length(data);
    AocArrayPtr uint_array = aoc_data_get(data);
    size_t      count = 0;
    for (size_t j = 0; j <= highest_bit_set; j++) {
        count = 0;
        for (size_t i = 0; i < length; i++) {
            bitfield = aoc_uint32_array_index(uint_array, i);
            count += (bitfield & (1u << j)) > 0;
            if ((2 * count / length) >= 1) {
                gamma_rate = gamma_rate | (1u << j);
                break;
            }
        }
    }
    epsilon_rate = gamma_rate ^ ((1u << (highest_bit_set + 1)) - 1);

    return strdup_printf("%u", gamma_rate * epsilon_rate);
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr oxygen_generator = NULL;
    AocArrayPtr co2_scrubber = NULL;
    AocArrayPtr og_tmp = NULL;
    AocArrayPtr co2s_tmp = NULL;

    uint32_t oxygen_generator_value;
    uint32_t co2_scrubber_value;
    uint8_t  value;
    uint8_t  init = 1;

    size_t digits = highest_bit_set;
    for (int j = digits; j >= 0; j--) {
        if (init) {
            value = common_value(aoc_data_get(data), j, 1);
            oxygen_generator = reduce(aoc_data_get(data), value, j);
            co2_scrubber = reduce(aoc_data_get(data), !value, j);
            init = 0;
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
    oxygen_generator_value = aoc_uint32_array_index(oxygen_generator, 0);
    co2_scrubber_value = aoc_uint32_array_index(co2_scrubber, 0);
    aoc_uint32_array_free(co2_scrubber);
    aoc_uint32_array_free(oxygen_generator);

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
    }
    aoc_data_free(data);

    return aoc_mem_gc();
}
