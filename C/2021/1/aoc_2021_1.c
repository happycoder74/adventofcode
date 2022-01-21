#include <stdio.h>
#include <stdlib.h>
#include "aoc_utils.h"

int solve_part_1(GArray *data) {
    gint i;
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
    gint i;
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


int main(int argc, char **argv) {
    GArray *data;
    char *filename;

    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "input.txt";
    }

    data = get_input(filename, 2021, 1);

    TIMER_INT(1, solve_part_1(data));
    TIMER_INT(2, solve_part_2(data));
}
