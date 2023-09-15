#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

// static bool point_is_equal(Point p0, Point p1) {
//     return ((p0.x == p1.x) && (p0.y == p1.y));
// }


GArray *clean_input(GArray *data) {
    GArray *lines_array = g_array_new(FALSE, FALSE, sizeof(Line *));

    for (guint i = 0; i < data->len; i++) {
        Point p0, p1;
        Line segment;
        gchar direction;
        gint length; 
        gchar *p;

        gchar *input = g_array_index(data, gchar *, i);
        GArray *line = g_array_new(FALSE, FALSE, sizeof(Line));

        gchar **steps = g_strsplit(input, ",", 0);

        p0.x = 0;
        p0.y = 0;
        for(gint step = 0; steps[step] != NULL; step++) {
            direction = steps[step][0];
            p = steps[step] + 1;
            length = atoi(p);
            switch(direction) {
                case 'U':
                    p1.x = p0.x;
                    p1.y = p0.y + length;
                    break;
                case 'D':
                    p1.x = p0.x;
                    p1.y = p0.y - length;
                    break;
                case 'L':
                    p1.x = p0.x - length;
                    p1.y = p0.y;
                    break;
                case 'R':
                    p1.x = p0.x + length;
                    p1.y = p0.y;
                    break;
            }
            segment.p0 = p0;
            segment.p1 = p1;
            g_array_append_val(line, segment);
            p0.x = p1.x;
            p0.y = p1.y;
        }
        g_array_append_val(lines_array, line);
    }

    return lines_array;
}

void *solve_part_1(AocData_t *data) {
    guint i, j;
    GArray *intersection_points = g_array_new(TRUE, TRUE, sizeof(Point));
    GArray *lines1 = g_array_index(data->data, GArray *, 0);
    GArray *lines2 = g_array_index(data->data, GArray *, 1);
    Line line1, line2;

    for (i = 0; i < lines1->len; i++) {
        for(j = 0; j < lines2->len; j++) {
            Point intersection_point;
            line1 = g_array_index(lines1, Line, i);
            line2 = g_array_index(lines2, Line, j);

            if(line_intersection(line1, line2, &intersection_point)) {
                #ifndef NDEBUG
                printf("(%d, %d)\n", intersection_point.x, intersection_point.y);
                #endif
                g_array_append_val(intersection_points, intersection_point);
            }
        }
    }

    int min_distance = INT_MAX;
    Point starting_point = point_new(0, 0);
    for (i = 1; i < intersection_points->len; i++) {
        Point point = g_array_index(intersection_points, Point, i);
        min_distance = MIN(point_manhattan_distance(point, starting_point), min_distance);
    }

    return g_strdup_printf("%d", min_distance);
}

void *solve_part_2(AocData_t *data) {
    guint i, j;
    GArray *intersection_points = g_array_new(TRUE, TRUE, sizeof(Point));
    GArray *lines1 = g_array_index(data->data, GArray *, 0);
    GArray *lines2 = g_array_index(data->data, GArray *, 1);
    Line line1, line2;
    gint min_steps = INT_MAX;

    for (i = 0; i < lines1->len; i++) {
        for(j = 0; j < lines2->len; j++) {
            Point intersection_point;
            line1 = g_array_index(lines1, Line, i);
            line2 = g_array_index(lines2, Line, j);

            if(line_intersection(line1, line2, &intersection_point)) {
                #ifndef NDEBUG
                printf("(%d, %d)\n", intersection_point.x, intersection_point.y);
                #endif
                g_array_append_val(intersection_points, intersection_point);
            }
        }
    }

    for (i = 1; i < intersection_points->len; i++) {
        Line line;
        int steps1 = 0, steps2 = 0;
        int nsteps;
        // Point test_point;
        Point intersection_point = g_array_index(intersection_points, Point, i);

        printf("Intersection point (%d, %d)\n", intersection_point.x, intersection_point.y);
        for (j = 0; j < lines1->len; j++) {
            line = g_array_index(lines1, Line, j);
            bool is_on_line = point_on_line(intersection_point, line);
            if(!is_on_line) {
                nsteps = point_manhattan_distance(line.p0, line.p1);
#ifndef NDEBUG
                printf("nsteps = %d (%d, %d) -> (%d, %d)\n", nsteps, line.p0.x, line.p0.y, line.p1.x, line.p1.y);
                #endif
                steps1 += nsteps;
            } else {
                nsteps = point_manhattan_distance(line.p0, intersection_point);
                #ifndef NDEBUG
                line_print(line);
                printf("nsteps = %d (%d, %d) -> (%d, %d) (IP)\n", nsteps, line.p0.x, line.p0.y, intersection_point.x, intersection_point.y);
                #endif
                steps1 += nsteps;
                break;
            }
        }
        for (j = 0; j < lines2->len; j++) {
            line = g_array_index(lines2, Line, j);
            if(!point_on_line(intersection_point, line)) {
                nsteps = point_manhattan_distance(line.p0, line.p1);
                #ifndef NDEBUG
                printf("nsteps = %d (%d, %d) -> (%d, %d)\n", nsteps, line.p0.x, line.p0.y, line.p1.x, line.p1.y);
                #endif
                steps2 += nsteps;
            } else {
                nsteps = point_manhattan_distance(line.p0, intersection_point);
                #ifndef NDEBUG
                line_print(line);
                printf("nsteps = %d (%d, %d) -> (%d, %d) (IP)\n", nsteps, line.p0.x, line.p0.y, intersection_point.x, intersection_point.y);
                #endif
                steps2 += nsteps;
                break;
            }
        }
        min_steps = MIN((steps1 + steps2), min_steps);
    }
    
    return g_strdup_printf("%d", min_steps);
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

    const int year = 2019;
    const int day = 3;
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
