#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"


gint solve_part_1(GArray *data) {
    guint i;
    gchar *row;
    gint l, w, h;
    gint area = 0;

    for (i = 0; i < data->len; i++) {
        row = g_array_index(data, char *, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        area += 2*l*w + 2*w*h + 2*h*l + MIN(MIN(l*w, w*h), h*l);
    }
    return area;
}

gint solve_part_2(GArray *data) {
    guint i;
    gchar *row;
    gint l, w, h;
    gint ribbon = 0;

    for (i = 0; i < data->len; i++) {
        row = g_array_index(data, char *, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        ribbon += MIN(MIN(2*w + 2*l, 2*w + 2*h), 2*h + 2*l) + l*w*h;
    }
    return ribbon;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = get_input(filename, year, day);

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

    TIMER(0, solve_all(filename, 2015, 2), INT, 0);

    g_free(filename);
}
