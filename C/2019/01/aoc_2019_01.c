#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glib.h"
#include "aoc_utils.h"

gint fuel_cost(gint fuel) {
    fuel = (fuel / 3) - 2;
    if (fuel < 0) {
        return 0;
    } else {
        return fuel + fuel_cost(fuel);
    }
}

GArray *clean_data(GArray *data) {
    GArray *return_data = g_array_new(FALSE, FALSE, sizeof(gint));
    guint i;
    guint val;

    for (i = 0; i < data->len; i++) {
        val = atoi(g_array_index(data, char *, i));
        g_array_append_val(return_data, val);
    }
    return return_data;
}

gpointer solve_part_1(AocData_t *data) {
    guint i;
    guint fuel = 0;
    gint val;

    for (i = 0; i < data->data->len; i++) {
        val = g_array_index(data->data, int, i);
        fuel += (val / 3) - 2;
    }
    return g_strdup_printf("%d", fuel);
}

gpointer solve_part_2(AocData_t *data) {
    guint i;
    gint val;
    guint fuel = 0;
    guint sum_fuel = 0;

    for (i = 0; i < data->data->len; i++) {
        val = g_array_index(data->data, int, i);
        fuel = (val / 3) - 2;
        sum_fuel += fuel + fuel_cost(fuel);
    }
    return g_strdup_printf("%d", sum_fuel);
}

gpointer solve_all(AocData_t *data) {

    data->data = clean_data(get_input(data->filename, data->year, data->day));

    if (data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return 0;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = aoc_data_new(filename, 2019, 1);
    g_free(filename);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
