#include "glib.h"
#include <stdio.h>
#include <string.h>

#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"

void *solve_part_1(AocData_t *data) {
    int level = 0;
    size_t i = 0;
    char *line;

    line = g_array_index(data->data, char *, i);

    for (i = 0; i < strlen(line); i++) {
        if (line[i] == '(')
            level += 1;
        else if (line[i] == ')')
            level -= 1;
    }
    return (void *)strdup_printf("%d", level);
}

void *solve_part_2(AocData_t *data) {
    size_t i = 0;
    int level = 0;

    char *line;

    line = g_array_index(data->data, char *, i);
    for (i = 0; i < strlen(line); i++) {
        if (line[i] == '(')
            level += 1;
        else if (line[i] == ')')
            level -= 1;
        if (level < 0)
            return (void *)strdup_printf("%d", i + 1);
    }
    return NULL;
}

void *solve_all(AocData_t *data) {

    data->data = get_input(data->filename, data->year, data->day);
    if (data->data) {
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

