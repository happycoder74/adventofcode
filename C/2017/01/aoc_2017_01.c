#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include "aoc_string.h"

typedef struct {
    int *data;
    int len;
} int_array;

int_array *get_input_bare(char *fn, int year, int day) {
    FILE *fp;
    int i;
    int_array *return_array;
    int c;

    char filename[1000];

    snprintf(filename, 1000, "../../data/%d/%02d/%s", year, day, fn);
    if (!(fp = fopen(filename, "r"))) {
        printf("Can not open '%s'\n", filename);
        exit(1);
    }

    i = 0;
    return_array = malloc(sizeof(int_array));
    return_array->data = NULL;
    while (((c = fgetc(fp)) != EOF) && (c != '\n')) {
        return_array->data = realloc(return_array->data, (i+1)*sizeof(int));
        return_array->data[i++] = c - '0';
    }

    aoc_array_length(return_array) = i;

    fclose(fp);
    return return_array;
}

int solve_part_1(int_array *data, int step) {
    int i, j;

    int sum = 0;

    for (i = 0; i < aoc_array_length(data); i++) {
        j = (i + step) % aoc_array_length(data);
        if (data->data[i] == data->data[j]) {
            sum += data->data[i];
        }
    }

    return sum;
}

int solve_part_2(int_array *data) {
    return solve_part_1(data, aoc_array_length(data) / 2);
}

int main(int argc, char **argv) {
    char *filename;

    if (argc > 1)
        filename = strdup(argv[1]);
    else
        filename = strdup("input.txt");
    int_array *data;

    data = get_input_bare(filename, 2017, 1);

    TIMER(1, solve_part_1(data, 1), INT, 1);
    TIMER(2, solve_part_2(data), INT, 1);

    free(data->data);
    free(data);
    free(filename);

    return 0;
}

