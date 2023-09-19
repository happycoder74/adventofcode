#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"

GArray *clean_input(GArray *data) {
    gchar *dataline;
    GArray *return_data;
    Line line;

    return_data = g_array_new(TRUE, FALSE, sizeof(Line));
    for (guint i = 0; i < data->len; i++) {
        dataline = g_array_index(data, gchar *, i);
        sscanf(dataline, "%d,%d -> %d,%d", &line.p0.x, &line.p0.y, &line.p1.x, &line.p1.y);
        if (is_horisontal(line)) {
            line.stepx = line.p0.x < line.p1.x ? 1 : -1;
            line.stepy = 0;
        } else if (is_vertical(line)) {
            line.stepx = 0;
            line.stepy = line.p0.y < line.p1.y ? 1 : -1;
        } else {
            line.stepx = line.p0.x < line.p1.x ? 1 : -1;
            line.stepy = line.p0.y < line.p1.y ? 1 : -1;
        }
        g_array_append_val(return_data, line);
    }

    g_array_unref(data);
    return return_data;
}

int mark_points(GHashTable *hashtable, Line line, gboolean diagonal) {
    Point point;
    int value;
    gpointer old_value;
    int count = 0;
    Point *key;

    if (!diagonal && is_diagonal(line)) {
        return 0;
    }

    for (point = line.p0;
            (point.x != (line.p1.x + line.stepx)) || (point.y != (line.p1.y + line.stepy));
            point.x += line.stepx, point.y += line.stepy) {
        if(g_hash_table_lookup_extended(hashtable, &point, NULL, &old_value)) {
            count++;
            value = GPOINTER_TO_INT(old_value) + 1;
        } else {
            value = 1;
        }
        key = point_new_m(point.x, point.y);
        g_hash_table_insert(hashtable, key, GINT_TO_POINTER(value));
    }

    return count;
}

void *solve_problem(GArray *data, gboolean diagonal) {
    GHashTable *hashtable;
    Line line;
    GHashTableIter iter;
    int count;
    gpointer key, value;

    hashtable = g_hash_table_new(point_hash, point_equal);

    for (guint i = 0; i < data->len; i++) {
        line = g_array_index(data, Line, i);
        mark_points(hashtable, line, diagonal);
    }

    count = 0;
    g_hash_table_iter_init(&iter, hashtable);
    while(g_hash_table_iter_next(&iter, &key, &value)) {
        if (GPOINTER_TO_INT(value) > 1)
            count++;
    }

    g_hash_table_unref(hashtable);

    return strdup_printf("%d", count);
}

void *solve_part_1(AocData_t *data) {
    return solve_problem(data->data, FALSE);
}

void *solve_part_2(AocData_t *data) {
    return solve_problem(data->data, TRUE);
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
    gchar *filename;

    gchar *sourcefile = basename(__FILE__);
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
