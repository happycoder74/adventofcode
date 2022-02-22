#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

int solve_part_1(GArray *data) {
    gint i = 0;
    gchar *line;
    int pos = 0, depth = 0;
    int value;
    char command[10] = {0};

    while ((line = g_array_index(data, gchar *, i++)) != NULL) {
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
    return depth * pos;
}

int solve_part_2(GArray *data) {
    gint i = 0;
    gchar *line;
    int pos = 0, depth = 0, aim = 0;
    int value;
    char command[10] = {0};

    while ((line = g_array_index(data, gchar *, i++)) != NULL) {
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
    return depth * pos;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = get_input_new(filename, year, day);

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), INT, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2021, 2), INT, 0);
    g_free(filename);
}
