#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    unsigned red;
    unsigned green;
    unsigned blue;
} Bag = {12, 13, 14};

unsigned max_color(const char *str, const char *color) {
    unsigned max_color = 0;
    char    *ptr;
    char    *ptr2;
    ptr = strstr(str, color);
    while (ptr != NULL) {
        unsigned n_color = 0;
        ptr2 = strchr(ptr - 4, ' ') + 1;
        sscanf(ptr2, "%u", &n_color);
        if (n_color > max_color) {
            max_color = n_color;
        }
        if ((ptr + 3) >= (str + strlen(str))) {
            ptr = NULL;
        } else {
            ptr = strstr(ptr + 3, color);
        }
    }

    return max_color;
}

void *solve_part_1(AocData_t *data) {
    unsigned    valid = 0;
    AocArrayPtr input = aoc_data_get(data);

    for (unsigned i = 0; i < input->length; i++) {
        char *str = aoc_str_array_index(input, i);
        if ((max_color(str, "red") <= Bag.red) && (max_color(str, "green") <= Bag.green) && (max_color(str, "blue") <= Bag.blue)) {
            valid += (i + 1);
        }
    }

    return strdup_printf("%d", valid);
}

void *solve_part_2(AocData_t *data) {
    uint32_t sum = 0;

    AocArrayPtr input = aoc_data_get(data);
    for (unsigned i = 0; i < input->length; i++) {
        char *str = aoc_str_array_index(input, i);
        sum += max_color(str, "red") * max_color(str, "green") * max_color(str, "blue");
    }

    return strdup_printf("%d", sum);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2023;
    const unsigned day = 2;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
