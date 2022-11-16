#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include "aoc_timer.h"

GArray *clean_input(GArray *data) {
    return data;
}


gint solution(GArray *data, gboolean part_two) {
    gchar **split_string;
    gint i;
    gint *pos;
    gint *current;
    GHashTable *locations;
    GArray *directions;
    typedef struct {
        gchar direction;
        gint steps;
    } step_t;

    step_t *step = g_new(step_t, 1);

    directions = g_array_new(TRUE, TRUE, sizeof(int *));
    locations = g_hash_table_new(g_str_hash, g_str_equal);
    pos = g_new(gint, 2);
    pos[0] = 1;
    pos[1] = 0;
    g_array_append_val(directions, pos);
    pos = g_new(gint, 2);
    pos[0] = 0;
    pos[1] = 1;
    g_array_append_val(directions, pos);
    pos = g_new(gint, 2);
    pos[0] = -1;
    pos[1] = 0;
    g_array_append_val(directions, pos);
    pos = g_new(gint, 2);
    pos[0] = 0;
    pos[1] = -1;
    g_array_append_val(directions, pos);

    pos = g_new(gint, 2);
    pos[0] = 0;
    pos[1] = 0;


    if (part_two) {
        g_hash_table_add(locations, g_strdup_printf("(%d, %d)", pos[0], pos[1]));
    }
    split_string = g_strsplit(g_array_index(data, char *, 0), ", ", 0);
    int index = 0;
    int s = 0;
    step = g_new(step_t, 1);
    for (i = 0; split_string[i] != NULL; i++) {
        sscanf(split_string[i], "%c%d", &step->direction, &step->steps);
        index = index + (step->direction == 'R' ? 1 : -1);
        index = (index >= 0 ? index % 4 : 4 + (index % -4));
        current = g_array_index(directions, gint *, index);
        for (s = 0; s < step->steps; s++) {
            pos[0] = pos[0] + current[0];
            pos[1] = pos[1] + current[1];
            if (part_two) {
                if (g_hash_table_contains(locations, g_strdup_printf("(%d, %d)", pos[0], pos[1]))) {
                    return abs(pos[0]) + abs(pos[1]);
                }
                g_hash_table_add(locations, g_strdup_printf("(%d, %d)", pos[0], pos[1]));
            }
        }
    }
    g_free(step);
    g_array_free(directions, TRUE);

    return abs(pos[0] + pos[1]);


}

gpointer solve_part_1(AocData_t *data) {
    return g_strdup_printf("%d", solution(data->data, FALSE));
}

gpointer solve_part_2(AocData_t *data) {
    return g_strdup_printf("%d", solution(data->data, TRUE));
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

    data = aoc_data_new(filename, 2016, 1);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);
}
