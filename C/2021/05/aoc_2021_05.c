#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_array.h"
#include "aoc_timer.h"

AocArrayPtr clean_input(AocArrayPtr data) {
    char *dataline;
    AocArrayPtr return_data;
    Line line;

    return_data = aoc_line_array_new();
    for (unsigned int i = 0; i < aoc_array_length(data); i++) {
        dataline = aoc_str_array_index(data, i);
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
        aoc_line_array_append(return_data, line);
    }

    aoc_line_array_free(data);
    return return_data;
}

int mark_points(GHashTable *hashtable, Line line, int diagonal) {
    Point point;
    int value;
    void *old_value;
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
            value = (int)(int64_t)(old_value) + 1;
        } else {
            value = 1;
        }
        key = point_new_m(point.x, point.y);
        g_hash_table_insert(hashtable, key, (void *)(int64_t)(value));
    }

    return count;
}

void *solve_problem(AocArrayPtr data, int diagonal) {
    GHashTable *hashtable;
    Line line;
    GHashTableIter iter;
    int count;
    void *key, *value;

    hashtable = g_hash_table_new(point_hash, point_equal);

    for (unsigned int i = 0; i < aoc_array_length(data); i++) {
        line = aoc_line_array_index(data, i);
        mark_points(hashtable, line, diagonal);
    }

    count = 0;
    g_hash_table_iter_init(&iter, hashtable);
    while(g_hash_table_iter_next(&iter, &key, &value)) {
        if ((int)(int64_t)(value) > 1)
            count++;
    }

    g_hash_table_unref(hashtable);

    return strdup_printf("%d", count);
}

void *solve_part_1(AocData_t *data) {
    return solve_problem(aoc_data_get(data), FALSE);
}

void *solve_part_2(AocData_t *data) {
    return solve_problem(aoc_data_get(data), TRUE);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    } return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new_clean("test_input.txt", year, day, clean_input);
        } else {
            data = aoc_data_new_clean(argv[1], year, day, clean_input);
        }
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
