#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    char       *dataline;
    AocArrayPtr return_data;
    Line        line;

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

int mark_points(AocHashTable *hashtable, Line line, int diagonal) {
    Point  point;
    int    value;
    void  *old_value;
    int    count = 0;
    Point *key;

    if (!diagonal && is_diagonal(line)) {
        return 0;
    }

    for (point = line.p0;
         (point.x != (line.p1.x + line.stepx)) || (point.y != (line.p1.y + line.stepy));
         point.x += line.stepx, point.y += line.stepy) {
        if ((old_value = aoc_hash_table_lookup(hashtable, &point))) {
            count++;
            value = (int)(int64_t)(old_value) + 1;
        } else {
            value = 1;
        }
        key = point_new_m(point.x, point.y);
        aoc_hash_table_replace(hashtable, key, (void *)(int64_t)(value));
    }

    return count;
}

bool if_larger_than_1(const void *value) {
    return (((int)(int64_t)value) > 1);
}

void *solve_problem(AocArrayPtr data, int diagonal) {
    AocHashTable   *hashtable;
    Line            line;
    AocHashIterator iter;
    int             count;
    void           *key, *value;

    hashtable = aoc_hash_table_create_custom(100, NULL, NULL, NULL, AOC_POINT);
    /* hashtable = aoc_hash_table_create(AOC_POINT); */

    count = 0;
    for (unsigned int i = 0; i < aoc_array_length(data); i++) {
        line = aoc_line_array_index(data, i);
        count += mark_points(hashtable, line, diagonal);
    }

    AocArrayPtr values = aoc_hash_table_get_values_if(hashtable, if_larger_than_1);
    count = values->length;
    aoc_array_free(values, 0);

    aoc_hash_table_destroy(&hashtable);

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
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2021;
    const unsigned day = 5;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
