#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "aoc_utils.h"
#include "aoc_timer.h"
#include "aoc_array.h"

AocArrayPtr clean_input(AocArrayPtr data) {
    return data;
}

void *solve_part_1(AocData_t *data) {
    return NULL;
}

void *solve_part_2(AocData_t *data) {
    return NULL;
}

void *solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[100];
    int year, day;

    strcpy(sourcefile, basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, NULL);
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}

