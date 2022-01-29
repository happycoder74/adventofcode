#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

char *solve_part_1(GArray *data) {
    return NULL;
}

char *solve_part_2(GArray *data) {
    return NULL;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = get_input(filename, year, day);

    if (data) {
        TIMER(1, solve_part_1(data), STR, 1);
        TIMER(2, solve_part_2(data), STR, 1);

        g_array_free(data, TRUE);
    }
}
int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, <YEAR>, <DAY>), INT, 0);
    g_free(filename);
}
