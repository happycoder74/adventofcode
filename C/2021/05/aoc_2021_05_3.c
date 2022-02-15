#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

const int GRIDSIZE = 1000;

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

void mark_points(Grid *grid, Line line, gboolean diagonal) {
    Point point;
    gint value;

    if (!diagonal && is_diagonal(line)) {
        return;
    }

    for (point = line.p0;
            (point.x != (line.p1.x + line.stepx)) || (point.y != (line.p1.y + line.stepy));
            point.x += line.stepx, point.y += line.stepy) {
        value = grid_index(grid, point.y, point.x);
        grid_index_set(grid, point.y, point.x, value + 1);
    }
    return;
}


int solve_problem(GArray *data, gboolean diagonal) {
    Line line;
    gint row, col;
    gint count;
    Grid *grid;


    grid = grid_new(GRIDSIZE, GRIDSIZE);

    for (guint i = 0; i < data->len; i++) {
        line = g_array_index(data, Line, i);
        mark_points(grid, line, diagonal);
    }

    count = 0;
    for (row = 0; row < grid->rows; row++) {
        for (col = 0; col < grid->columns; col++) {
            if (grid_index(grid, row, col) > 1)
                count++;
        }
    }

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

