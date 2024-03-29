#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <string.h>

void *solve_part_1(AocData_t *data) {
    int    level = 0;
    size_t i = 0;
    char  *line;

    line = aoc_str_array_index(aoc_data_get(data), i);

    for (i = 0; i < strlen(line); i++) {
        if (line[i] == '(') {
            level += 1;
        } else if (line[i] == ')') {
            level -= 1;
        }
    }

    return (void *)strdup_printf("%d", level);
}

void *solve_part_2(AocData_t *data) {
    size_t i = 0;
    int    level = 0;

    char *line;

    line = aoc_str_array_index(aoc_data_get(data), i);

    for (i = 0; i < strlen(line); i++) {
        if (line[i] == '(') {
            level += 1;
        } else if (line[i] == ')') {
            level -= 1;
        }
        if (level < 0) {
            return (void *)strdup_printf("%d", i + 1);
        }
    }
    return NULL;
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2015;
    const unsigned day = 1;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
