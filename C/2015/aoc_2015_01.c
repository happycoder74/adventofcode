#define _XOPEN_SOURCE 600
#include "aoc_alloc.h"
#include "aoc_io.h"
#include "aoc_array.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_timer.h"
#include "aoc_string.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void *solve_part_1(void *data) {
    size_t i = 0;
    int level = 0;
    char *line = (char *)data;
    char c;
    for (i = 0; (c = line[i]); i++) {
        line[i] == '(' ? ++level : --level;
    }

    return (void *)strdup_printf("%d", level);
}

void *solve_part_2(void *data) {
    size_t i = 0;
    int level = 0;
    char *line = (char *)data;
    char c;

    for (i = 0; (c = line[i]); i++) {
        line[i] == '(' ? ++level : --level;
        if (level == -1) {
            return strdup_printf("%d", i + 1);
        }
    }
    return 0;
}

void *solve_all(void *data) {
    timer_func_new(1, solve_part_1, data, 1);
    timer_func_new(2, solve_part_2, data, 1);
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2015;
    const unsigned day = 1;

    AocData_t *data = get_data(argc, argv, year, day, NULL);
    char *line = aoc_str_array_index(data->data, 0);

    aoc_header(year, day);
    timer_func_new(0, solve_all, (void *)line, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
