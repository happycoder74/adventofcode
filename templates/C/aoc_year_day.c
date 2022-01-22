#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"


char* solve_part_1(GArray *data) {
    return NULL;
}

char *solve_part_2(GArray *data) {
    return NULL;
}


int main(int argc, char **argv) {
    GArray *data;
    gchar *filename;

    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = g_strdup("input.txt");
    }

    data = get_input(filename, year, day);

    if (data) {
        TIMER_STR(1, solve_part_1(data));
        TIMER_STR(2, solve_part_2(data));

        g_array_free(data, TRUE);
    }

}
