#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *solve_part_1(AocData_t *data) {
    uint32_t i = 0;
    char    *line;
    int      pos = 0, depth = 0;
    int      value;
    char     command[10] = {0};

    for (i = 0; i < aoc_data_length(data); i++) {
        line = aoc_str_array_index(aoc_data_get(data), i);
        sscanf(line, "%s %d", command, &value);
        if (!strcmp(command, "forward")) {
            pos += value;
        }
        if (!strcmp(command, "down")) {
            depth += value;
        }
        if (!strcmp(command, "up")) {
            depth -= value;
        }
    }
    return strdup_printf("%d", depth * pos);
}

void *solve_part_2(AocData_t *data) {
    uint32_t i = 0;
    char    *line;
    int      pos = 0, depth = 0, aim = 0;
    int      value;
    char     command[10] = {0};

    for (i = 0; i < aoc_data_length(data); i++) {
        line = aoc_str_array_index(aoc_data_get(data), i);
        sscanf(line, "%s %d", command, &value);
        if (!strcmp(command, "forward")) {
            pos += value;
            depth += value * aim;
        }
        if (!strcmp(command, "down")) {
            aim += value;
        }
        if (!strcmp(command, "up")) {
            aim -= value;
        }
    }
    return strdup_printf("%d", depth * pos);
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
    const unsigned day = 2;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
