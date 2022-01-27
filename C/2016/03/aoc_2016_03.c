#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

int is_valid_i(int a, int b, int c) {
    return (a + b > c) && (b + c > a) && (c + a > b);
}

int is_valid(char *sides) {
    int a, b, c;

    sscanf(str_trim(sides), "%d %d %d", &a, &b, &c);
    return is_valid_i(a, b, c);
}

int solve_part_1(GArray *data) {
    int count;
    guint i;

    count = 0;
    for (i = 0; i < data->len; i++) {
        if(is_valid(g_array_index(data, char *, i))) {
            count++;
        }
    }
    return count;
}

int solve_part_2(GArray *data) {
    int *int_array[3];
    guint i, j;
    int count = 0;
    for (i = 0; i < 3; i++) {
        int_array[i] = malloc(sizeof(int) * data->len);
    }

    for (i = 0; i < data->len; i++) {
        sscanf(g_array_index(data, char *, i), "%d %d %d",
                &int_array[0][i], &int_array[1][i], &int_array[2][i]);
    }

    for (j = 0; j < 3; j++) {
        for (i = 0; i < data->len - 2; i += 3) {
            if (is_valid_i(int_array[j][i], int_array[j][i + 1], int_array[j][i + 2]))
                count++;
        }
    }


    return count;
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

    TIMER(0, solve_all(filename, 2016, 3), INT, 0);
    g_free(filename);

    return 0;
}
