#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <assert.h>
#include "aoc_utils.h"

GArray *clean_input(GArray *data) {
    gchar **split_string;
    GArray *return_data = g_array_new(TRUE, FALSE, sizeof(int));
    gint value;
    split_string = g_strsplit(g_array_index(data, gchar *, 0), ",", -1);
    for (gint i = 0; split_string[i] != NULL; i++) {
        sscanf(split_string[i], "%d", &value);
        g_array_append_val(return_data, value);
    }

    g_strfreev(split_string);
    g_array_unref(data);
    return return_data;
}

unsigned long long  lantern_fish_evolve(GArray *data, gint days) {
    unsigned long long *school_of_fish;
    unsigned long long sum = 0;
    const guint school_size = 9;
    guint tail, head;

    school_of_fish = g_new0(unsigned long long, school_size);
    for (guint i = 0; i < data->len; i++) {
        school_of_fish[g_array_index(data, int, i)] += 1;
    }

    tail = 8;
    head = tail - 2;
    for (gint day = 1; day <= days; day++) {
        tail = (1 + tail) == school_size ? 0 : 1 + tail;
        head = (1 + head) == school_size ? 0 : 1 + head;
        school_of_fish[head] += school_of_fish[tail];
    }

    for (guint i = 0; i < school_size; i++) {
        sum += school_of_fish[i];
    }

    return sum;
}

unsigned long long solve_part_1(GArray *data) {
    return lantern_fish_evolve(data, 80);
}

unsigned long long solve_part_2(GArray *data) {
    return lantern_fish_evolve(data, 256);
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = clean_input(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), ULONG, 1);
        TIMER(2, solve_part_2(data), ULONG, 1);

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

    TIMER(0, solve_all(filename, 2021, 6), INT, 0);
    g_free(filename);
}
