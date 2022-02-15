#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

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

gboolean is_diagonal (Line line) {
    return (!is_horisontal(line)) && (!is_vertical(line));
}

void print_point(Point p) {
    g_print("Point (%d, %d)\n", p.x, p.y);
    return;
}

gboolean point_eq(Point p1, Point p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
}

Point *point_dup(Point p) {
    Point *point;
    point = g_new(Point, 1);
    point->x = p.x;
    point->y = p.y;

    return point;
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
        key = point_dup(point);
        g_hash_table_insert(hashtable, key, GINT_TO_POINTER(value));
    }

    return count;
}

GHashTable *create_points_hash_table() {
    GHashTable *hashtable;

    hashtable = g_hash_table_new(point_hash, point_equal);

    return hashtable;
}

int solve_problem(GArray *data, gboolean diagonal) {
    GHashTable *hashtable;
    Line line;
    GHashTableIter iter;
    int count;
    gpointer key, value;

    hashtable = create_points_hash_table();

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

    return count;
}
int solve_part_1(GArray *data) {
    return solve_problem(data, FALSE);
}

int solve_part_2(GArray *data) {
    return solve_problem(data, TRUE);
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

    TIMER(0, solve_all(filename, 2021, 5), INT, 0);
    g_free(filename);
}
