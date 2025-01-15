#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int marker(AocArrayPtr data, size_t window) {
    size_t i, j;
    char  *string;
    char  *chunk;

    chunk = (char *)calloc(window + 1, sizeof(char));
    string = (char *)aoc_ptr_array_index(data, 0);
    for (i = 0; i < strlen(string) - window; i++) {
        chunk[0] = '\0';
        for (j = 0; j < window; j++) {
            if (strchr(chunk, string[i + j])) {
                break;
            } else {
                chunk[j] = string[i + j];
                chunk[j + 1] = '\0';
            }
            if (strlen(chunk) == window) {
                free(chunk);
                return i + window;
            }
        }
    }
    free(chunk);
    return 0;
}

void *solve_part_1(AocData_t *data) {
    return strdup_printf("%d", marker(aoc_data_get(data), 4));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%d", marker(aoc_data_get(data), 14));
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2022;
    const unsigned day = 6;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
