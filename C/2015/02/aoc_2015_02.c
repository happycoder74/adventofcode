#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"


gpointer solve_part_1(AocData_t *data) {
    guint i;
    gchar *row;
    gint l, w, h;
    gint area = 0;

    for (i = 0; i < data->data->len; i++) {
        row = g_array_index(data->data, char *, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        area += 2*l*w + 2*w*h + 2*h*l + MIN(MIN(l*w, w*h), h*l);
    }
    return g_strdup_printf("%d", area);
}

gpointer solve_part_2(AocData_t *data) {
    guint i;
    gchar *row;
    gint l, w, h;
    gint ribbon = 0;

    for (i = 0; i < data->data->len; i++) {
        row = g_array_index(data->data, char *, i);
        sscanf(row, "%dx%dx%d", &l, &w, &h);
        ribbon += MIN(MIN(2*w + 2*l, 2*w + 2*h), 2*h + 2*l) + l*w*h;
    }
    return g_strdup_printf("%d", ribbon);
}

gpointer solve_all(AocData_t *data) {
    data->data = get_input(data->filename, data->year, data->day);

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

    data = aoc_data_new(filename, 2015, 2);
    g_free(filename);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
