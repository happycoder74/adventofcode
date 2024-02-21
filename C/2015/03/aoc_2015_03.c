#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include "glib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solver(AocArrayPtr data, uint32_t agents) {
    char       *line;
    GHashTable *visited;
    Point      *position;
    size_t      visited_size;
    size_t      position_index = 0;
    Point      *key;

    position = (Point *)calloc(agents, sizeof(Point));
    visited = g_hash_table_new_full(point_hash, point_equal, free, NULL);

    key = (Point *)calloc(1, sizeof(Point));
    key->x = position[position_index].x;
    key->y = position[position_index].y;
    g_hash_table_add(visited, key);

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
        g_hash_table_add(visited, key);
    }
    visited_size = g_hash_table_size(visited);

    free(position);
    g_hash_table_destroy(visited);
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
    AocData_t *data;

    char sourcefile[20];
    int  year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new("test_input.txt", year, day);
        } else {
            data = aoc_data_new(argv[1], year, day);
        }
    } else {
        data = aoc_data_new_clean("input.txt", year, day, NULL);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
