#include <stdio.h>
#include <stdlib.h>
#include "aoc_utils.h"
#include "aoc_string.h"

GArray *clean_data(GArray *data) {
    return data;
}

void *solve_part_1(AocData_t *data) {
    size_t i;
    int count = 0;
    char *val1, *val2;

    for (i = 1; i < data->data->len; i++) {
        val1 = g_array_index(data->data, char *, i - 1);
        val2 = g_array_index(data->data, char *, i);
        if (atoi(val2) > atoi(val1)) {
            count ++;
        }
    }
    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    size_t i;
    int count = 0;
    char *val1, *val2;

    for (i = 3; i < data->data->len; i++) {
        val1 = g_array_index(data->data, char *, i - 3);
        val2 = g_array_index(data->data, char *, i);
        if (atoi(val2) > atoi(val1)) {
            count ++;
        }
    }
    return strdup_printf("%d", count);
}


void *solve_all(AocData_t *data) {

    data->data = clean_data(get_input(data->filename, data->year, data->day));

    if (data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    char *sourcefile;
    int year, day;

    sourcefile = basename(__FILE__);
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);

    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
