#include <stdio.h>
#include <stdlib.h>
#include "aoc_utils.h"

GArray *clean_data(GArray *data) {
    return data;
}

int solve_part_1(GArray *data) {
    guint i;
    gint count = 0;
    char *val1, *val2;

    for (i = 1; i < data->len; i++) {
        val1 = g_array_index(data, char *, i - 1);
        val2 = g_array_index(data, char *, i);
        if (atoi(val2) > atoi(val1)) {
            count ++;
        }
    }
    return count;
}

int solve_part_2(GArray *data) {
    guint i;
    gint count = 0;
    char *val1, *val2;

    for (i = 3; i < data->len; i++) {
        val1 = g_array_index(data, char *, i - 3);
        val2 = g_array_index(data, char *, i);
        if (atoi(val2) > atoi(val1)) {
            count ++;
        }
    }
    return count;
}


int solve_all(char *filename, int year, int day) {
    GArray *data;

    data = clean_data(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), INT, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    char *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2021, 1), INT, 0);

    g_free(filename);

}
