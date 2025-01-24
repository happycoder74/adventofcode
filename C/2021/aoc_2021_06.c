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

AocArrayPtr clean_input(AocArrayPtr data) {
    char      **split_string;
    AocArrayPtr return_data = aoc_int_array_new();
    int         value;
    split_string = aoc_str_split(aoc_str_array_index(data, 0), ",", -1);
    for (int i = 0; split_string[i] != NULL; i++) {
        sscanf(split_string[i], "%d", &value);
        aoc_int_array_append(return_data, value);
    }

    aoc_str_freev(split_string);
    aoc_int32_array_free(data);
    return return_data;
}

uint64_t lantern_fish_evolve(AocArrayPtr data, int days) {
    uint64_t          *school_of_fish;
    uint64_t           sum = 0;
    const unsigned int school_size = 9;
    unsigned int       tail, head;

    school_of_fish = (uint64_t *)calloc(school_size, sizeof(uint64_t));
    for (unsigned int i = 0; i < aoc_array_length(data); i++) {
        school_of_fish[aoc_int_array_index(data, i)] += 1;
    }

    tail = 8;
    head = tail - 2;
    for (int day = 1; day <= days; day++) {
        tail = (1 + tail) == school_size ? 0 : 1 + tail;
        head = (1 + head) == school_size ? 0 : 1 + head;
        school_of_fish[head] += school_of_fish[tail];
    }

    for (unsigned int i = 0; i < school_size; i++) {
        sum += school_of_fish[i];
    }

    return sum;
}

void *solve_part_1(AocData_t *data) {
    return strdup_printf("%llu", lantern_fish_evolve(data->data, 80));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%llu", lantern_fish_evolve(data->data, 256));
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2021;
    const unsigned day = 6;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
