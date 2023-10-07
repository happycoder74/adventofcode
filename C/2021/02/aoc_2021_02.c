#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_array.h"

void *solve_part_1(AocData_t *data) {
    uint32_t i = 0;
    char *line;
    int pos = 0, depth = 0;
    int value;
    char command[10] = {0};

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
    char *line;
    int pos = 0, depth = 0, aim = 0;
    int value;
    char command[10] = {0};

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
    } return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new(argv[1], year, day);
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
