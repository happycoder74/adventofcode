#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

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
gint solve_part_1(GArray *data) {
    return solution(data, FALSE);
}

int solve_part_2(GArray *data) {
    return solution(data, TRUE);
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

    TIMER(0, solve_all(filename, 2016, 1), INT, 0);
    g_free(filename);
}
