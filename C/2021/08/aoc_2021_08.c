#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

GArray *clean_input(GArray *data) {
    GArray *result;
    guint i;
    gchar **split_line;

    result = g_array_new(TRUE, FALSE, sizeof(gchar **));
    for (i = 0; i < data->len; i++) {
        split_line = g_strsplit(g_array_index(data, gchar *, i), "|", -1);
        g_array_append_val(result, split_line);
    }

    return result;
}

int solve_part_1(GArray *data) {
    gchar **split_line;
    gchar **output_value;
    gchar *val;
    gint count = 0;
    for (guint i = 0; i < data->len; i++) {
        split_line = g_array_index(data, char **, i);
        output_value = g_strsplit(g_strstrip(split_line[1]), " ", -1);

        gint j = 0;
        while ((val = output_value[j]) != NULL) {
            if ((strlen(val) >= 2 && strlen(val) <=4) || strlen(val) == 7) {
                count++;
            }
            j++;
        }

    }
    return count;
}

char *solve_part_2(GArray *data) {
    return NULL;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = clean_input(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), STR, 1);

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

    TIMER(0, solve_all(filename, 2021, 8), INT, 0);
    g_free(filename);
}
