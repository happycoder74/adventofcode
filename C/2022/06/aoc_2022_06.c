#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <libgen.h>
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"

int marker(GArray *data, size_t window) {
    size_t i, j;
    char *string;
    char *chunk;

    chunk = (char *)calloc((size_t)window + 1, sizeof(char));
    string = g_array_index(data, char *, 0);
    for (i = 0; i < strlen(string) - window; i++) {
        chunk[0] = '\0';
        for (j = 0; j < window; j++) {
            if(strchr(chunk, string[i + j])) {
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
    return strdup_printf("%d", marker(data->data, 4));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%d", marker(data->data, 14));
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    int year, day;
    char sourcefile[100];

    strcpy(sourcefile, basename(__FILE__));
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
