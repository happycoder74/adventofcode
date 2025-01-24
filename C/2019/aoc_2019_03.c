#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr lines_array = aoc_ptr_array_new();

    for (unsigned int i = 0; i < aoc_array_length(data); i++) {
        Point p0, p1;
        Line  segment;
        char  direction;
        int   length;
        char *p;

        char       *input = aoc_str_array_index(data, i);
        AocArrayPtr line = aoc_line_array_new();

        char **steps = aoc_str_split(input, ",", 0);

        p0.x = 0;
        p0.y = 0;
        for (int step = 0; steps[step] != NULL; step++) {
            direction = steps[step][0];
            p = steps[step] + 1;
            length = atoi(p);
            switch (direction) {
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
                default:
                    fprintf(stderr, "Error in direction input\n");
                    exit(EXIT_FAILURE);
            }
            segment.p0 = p0;
            segment.p1 = p1;
            aoc_line_array_append(line, segment);
            p0.x = p1.x;
            p0.y = p1.y;
        }
        aoc_ptr_array_append(lines_array, line);
        aoc_str_freev(steps);
    }

    return lines_array;
}

void *solve_part_1(AocData_t *data) {
    unsigned int i, j;
    AocArrayPtr  intersection_points = aoc_point_array_new();
    AocArrayPtr  lines1 = (AocArrayPtr)aoc_ptr_array_index(aoc_data_get(data), 0);
    AocArrayPtr  lines2 = (AocArrayPtr)aoc_ptr_array_index(aoc_data_get(data), 1);
    Line         line1, line2;

    for (i = 0; i < aoc_array_length(lines1); i++) {
        for (j = 0; j < aoc_array_length(lines2); j++) {
            Point intersection_point;
            line1 = aoc_line_array_index(lines1, i);
            line2 = aoc_line_array_index(lines2, j);

            if (line_intersection(line1, line2, &intersection_point)) {
                aoc_point_array_append(intersection_points, intersection_point);
            }
        }
    }

    int   min_distance = INT_MAX;
    Point starting_point = {0, 0};
    for (i = 1; i < aoc_array_length(intersection_points); i++) {
        Point point = aoc_point_array_index(intersection_points, i);
        min_distance = MIN(point_manhattan_distance(point, starting_point), min_distance);
    }

    return strdup_printf("%d", min_distance);
}

AocArrayPtr set_intersection(AocHashTable *table1, AocHashTable *table2) {
    AocArrayPtr     result = aoc_ptr_array_new();
    AocHashIterator iter;
    void           *key, *value;

    aoc_hash_table_iter_init(&iter, table1);
    while (aoc_hash_table_iter_next(&iter, &key, &value)) {
        if (aoc_hash_table_contains(table2, key)) {
            aoc_ptr_array_append(result, key);
        }
    }
    return result;
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr   lines[2];
    AocHashTable *line_coords[2];
    AocHashTable *line_stepmap[2];
    int           signal = 0, min_signal = INT_MAX;
    AocArrayPtr   intersections;

    lines[0] = (AocArrayPtr)aoc_ptr_array_index(aoc_data_get(data), 0);
    lines[1] = (AocArrayPtr)aoc_ptr_array_index(aoc_data_get(data), 1);

    line_coords[0] = aoc_hash_table_create_custom(30, NULL, free, NULL, AOC_POINT);
    line_coords[1] = aoc_hash_table_create_custom(30, NULL, free, NULL, AOC_POINT);

    // Using the same keys as line_coords why no free function is needed
    line_stepmap[0] = aoc_hash_table_create(AOC_POINT);
    line_stepmap[1] = aoc_hash_table_create(AOC_POINT);

    for (unsigned int wire = 0; wire < 2; wire++) {
        Point       *curr = point_new_m(0, 0);
        unsigned int steps = 0;
        Point        step;

        for (unsigned int i = 0; i < aoc_array_length(lines[wire]); i++) {
            Line         line = aoc_line_array_index(lines[wire], i);
            unsigned int length = line_length(line);
            if (is_horisontal(line)) {
                step.x = (line.p1.x - line.p0.x) / (int)length;
                step.y = 0;
            } else {
                step.x = 0;
                step.y = (line.p1.y - line.p0.y) / (int)length;
            }
            for (unsigned int j = 0; j < length; j++) {
                curr = point_new_m(curr->x + step.x, curr->y + step.y);
                steps += 1;
                aoc_hash_table_insert(line_stepmap[wire], curr, (void *)(int64_t)(steps));
                aoc_hash_table_add(line_coords[wire], curr);
            }
        }
    }

    // g_hash_table_foreach(line_coords[0], print_coords, NULL);
    intersections = set_intersection(line_coords[0], line_coords[1]);

    for (unsigned int i = 0; i < aoc_array_length(intersections); i++) {
        Point *intersection_point = (Point *)aoc_ptr_array_index(intersections, i);

        signal = (int)(int64_t)(aoc_hash_table_lookup(line_stepmap[0], intersection_point)) +
                 (int)(int64_t)(aoc_hash_table_lookup(line_stepmap[1], intersection_point));
        min_signal = MIN(signal, min_signal);
    }

    aoc_hash_table_destroy(&line_coords[0]);
    aoc_hash_table_destroy(&line_coords[1]);
    aoc_hash_table_destroy(&line_stepmap[0]);
    aoc_hash_table_destroy(&line_stepmap[1]);

    return strdup_printf("%d", min_signal);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2019;
    const unsigned day = 3;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
