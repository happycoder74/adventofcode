#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solver(AocArrayPtr data, uint32_t agents) {
    char         *line;
    AocHashTable *visited;
    Point        *position;
    size_t        visited_size;
    size_t        position_index = 0;
    Point        *key;

    position = (Point *)calloc(agents, sizeof(Point));
    visited = aoc_hash_table_create(3000, NULL, AOC_KEY_POINT);

    key = (Point *)calloc(1, sizeof(Point));
    key->x = position[position_index].x;
    key->y = position[position_index].y;
    aoc_hash_table_insert(visited, point_key(*key), key);

    line = aoc_str_array_index(data, 0);
    for (size_t c = 0; c < strlen(line); c++) {
        position_index = c % agents;
        switch (line[c]) {
            case '<':
                position[position_index].x -= 1;
                break;
            case '>':
                position[position_index].x += 1;
                break;
            case '^':
                position[position_index].y += 1;
                break;
            case 'v':
                position[position_index].y -= 1;
                break;
            default:
                break;
        }
        key = (Point *)calloc(1, sizeof(Point));
        key->x = position[position_index].x;
        key->y = position[position_index].y;
        aoc_hash_table_insert(visited, point_key(*key), key);
    }
    visited_size = aoc_hash_table_count(visited);

    free(position);
    return visited_size;
}

void *solve_part_1(AocData_t *data) {
    return strdup_printf("%d", solver(data->data, 1));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%d", solver(data->data, 2));
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2015;
    const unsigned day = 3;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
