#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

GArray *clean_input(GArray *data) {
    GArray *return_data = g_array_new(FALSE, FALSE, sizeof(int));
    gchar *row;
    guint i = 0;
    guint elf_sum = 0;
    for (i = 0; i < data->len; i++) {
        row = g_array_index(data, char *, i);
        if (strlen(row) > 0) {
            elf_sum += atoi(row);
        } else {
            g_array_append_val(return_data, elf_sum);
            elf_sum = 0;
        }
    }
    if (elf_sum != 0)
        g_array_append_val(return_data, elf_sum);

    return return_data;
}

int sort_int_desc(gconstpointer a, gconstpointer b) {
    int *_a = (int *)a;
    int *_b = (int *)b;
    return (*_b) - (*_a);
}

gpointer solve_part_1(AocData_t *data) {
    g_array_sort(data->data, sort_int_desc);
    return g_strdup_printf("%d", g_array_index(data->data, int, 0));
}

gpointer solve_part_2(AocData_t *data) {
    guint i;
    guint return_sum = 0;

    // Since array is already sorted from part 1
    // we can just return the sum of the three first
    // items.
    for(i = 0; i < 3; i++) {
        return_sum += g_array_index(data->data, int, i);
    }
    return g_strdup_printf("%d", return_sum);
}

gpointer solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

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

    data = aoc_data_new(filename, 2022, 1);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}