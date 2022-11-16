#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

gpointer solve_part_1(AocData_t *data) {
    gint i = 0;
    gchar *line;
    int pos = 0, depth = 0;
    int value;
    char command[10] = {0};

    while ((line = g_array_index(data->data, gchar *, i++)) != NULL) {
        sscanf(line, "%s %d", command, &value);
        if (!strcmp(command, "forward")) {
            pos += value;
        }
        if (!strcmp(command, "down")) {
            depth += value;
        }
        if (!strcmp(command, "up")) {
            depth -= value;
        }
    }
    return g_strdup_printf("%d", depth * pos);
}

gpointer solve_part_2(AocData_t *data) {
    gint i = 0;
    gchar *line;
    int pos = 0, depth = 0, aim = 0;
    int value;
    char command[10] = {0};

    while ((line = g_array_index(data->data, gchar *, i++)) != NULL) {
        sscanf(line, "%s %d", command, &value);
        if (!strcmp(command, "forward")) {
            pos += value;
            depth += value * aim;
        }
        if (!strcmp(command, "down")) {
            aim += value;
        }
        if (!strcmp(command, "up")) {
            aim -= value;
        }
    }
    return g_strdup_printf("%d", depth * pos);
}

gpointer solve_all(AocData_t *data) {
    data->data = get_input_new(data->filename, data->year, data->day);

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = aoc_data_new(filename, 2021, 2);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
