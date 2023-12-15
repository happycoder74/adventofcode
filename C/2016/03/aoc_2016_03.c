#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>

int is_valid_i(int a, int b, int c) {
    return (a + b > c) && (b + c > a) && (c + a > b);
}

int is_valid(char *sides) {
    int a, b, c;

    sscanf(str_trim(sides), "%d %d %d", &a, &b, &c);
    return is_valid_i(a, b, c);
}

void *solve_part_1(AocData_t *data) {
    int          count;
    unsigned int i;

    count = 0;
    for (i = 0; i < aoc_data_length(data); i++) {
        if (is_valid(aoc_str_array_index(aoc_data_get(data), i))) {
            count++;
        }
    }
    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    int         *int_array[3];
    unsigned int i, j;
    int          count = 0;
    for (i = 0; i < 3; i++) {
        int_array[i] = malloc(sizeof(int) * aoc_data_length(data));
    }

    for (i = 0; i < aoc_data_length(data); i++) {
        sscanf(aoc_str_array_index(aoc_data_get(data), i), "%d %d %d", &int_array[0][i], &int_array[1][i], &int_array[2][i]);
    }

    for (j = 0; j < 3; j++) {
        for (i = 0; i < aoc_data_length(data) - 2; i += 3) {
            if (is_valid_i(int_array[j][i], int_array[j][i + 1], int_array[j][i + 2]))
                count++;
        }
    }

    return strdup_printf("%d", count);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int  year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new("test_input.txt", year, day);
        } else {
            data = aoc_data_new(argv[1], year, day);
        }
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
