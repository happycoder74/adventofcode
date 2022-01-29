#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"


int find_min(GArray *array) {
    int min;
    guint i;

    min = g_array_index(array, int, 0);
    for (i = 1; i < array->len; i++) {
        min = MIN(min, g_array_index(array, int, i));
    }
    return min;
}

int find_max(GArray *array) {
    int max;
    guint i;

    max = g_array_index(array, int, 0);
    for (i = 1; i < array->len; i++) {
        max = MAX(max, g_array_index(array, int, i));
    }
    return max;
}

GArray *clean_input(GArray *data) {
    GArray *result;
    gchar **split_line;
    gchar *line;
    line = g_array_index(data, gchar *, 0);
    split_line = g_strsplit(line, ",", -1);
    int i, value;

    result = g_array_new(FALSE, FALSE, sizeof(int));

    i = 0;
    while (split_line[i] != NULL) {
        sscanf(split_line[i], "%d", &value);
        g_array_append_val(result, value);
        i++;
    }
    g_strfreev(split_line);
    return result;
}

int calc_fuel(GArray *data, int position, int part) {
    if (part == 1) {
        int sum = 0;
        for (guint i = 0; i < data->len; i++) {
            sum += abs(g_array_index(data, int, i) - position);
        }
        return sum;
    } else {
        int sum = 0;
        for (guint i = 0; i < data->len; i++) {
            int d = abs(g_array_index(data, int, i) - position);
            for (int j = 0; j <= d; j++) {
                sum += j;
            }
        }
        return sum;
    }
}

int solve_part_1(GArray *data) {
    int min_fuel, fuel, pos;

    min_fuel = calc_fuel(data, find_min(data), 1);

    for (guint i = 0; i < data->len; i ++) {
        pos = g_array_index(data, int, i);
        fuel = calc_fuel(data, pos, 1);
        if (fuel < min_fuel) {
            min_fuel = fuel;
        }
    }
    return min_fuel;
}

int solve_part_2(GArray *data) {
    int min_fuel, fuel;

    min_fuel = calc_fuel(data, find_min(data), 2);

    for (guint i = 0; i < (guint)find_max(data); i++) {
        fuel = calc_fuel(data, i, 2);
        if (fuel < min_fuel) {
            min_fuel = fuel;
        }
    }
    return min_fuel;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = clean_input(get_input(filename, year, day));

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

    TIMER(0, solve_all(filename, 2021, 7), INT, 0);
    g_free(filename);
}
