#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <assert.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"

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

void *solve_part_1(AocData_t *data) {
    return strdup_printf("%llu", lantern_fish_evolve(data->data, 80));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%llu", lantern_fish_evolve(data->data, 256));
}

void *solve_all(AocData_t *data) {
    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}


int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    char *sourcefile = basename(__FILE__);
    int year, day;
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);


    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
