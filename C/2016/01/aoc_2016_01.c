#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_key(void *key) {
    aoc_free(key);
}

int solution(AocArrayPtr data, int part_two) {
    char      **split_string;
    int         i;
    int        *pos;
    int        *current;
    GHashTable *locations;
    AocArrayPtr directions;
    typedef struct {
        char direction;
        int  steps;
    } step_t;

    step_t *step = (step_t *)aoc_malloc(sizeof(step_t));

    directions = aoc_ptr_array_new();
    locations = g_hash_table_new_full(g_str_hash, g_str_equal, free_key, NULL);
    pos = (int *)aoc_malloc(sizeof(int) * 2);
    pos[0] = 1;
    pos[1] = 0;
    aoc_ptr_array_append(directions, pos);
    pos = (int *)aoc_malloc(sizeof(int) * 2);
    pos[0] = 0;
    pos[1] = 1;
    aoc_ptr_array_append(directions, pos);
    pos = (int *)aoc_malloc(sizeof(int) * 2);
    pos[0] = -1;
    pos[1] = 0;
    aoc_ptr_array_append(directions, pos);
    pos = (int *)aoc_malloc(sizeof(int) * 2);
    pos[0] = 0;
    pos[1] = -1;
    aoc_ptr_array_append(directions, pos);

    pos = (int *)aoc_malloc(sizeof(int) * 2);
    pos[0] = 0;
    pos[1] = 0;

    if (part_two) {
        g_hash_table_add(locations, strdup_printf("(%d, %d)", pos[0], pos[1]));
    }
    split_string = aoc_str_split(aoc_str_array_index(data, 0), ", ", 0);
    int index = 0;
    int s = 0;
    for (i = 0; split_string[i] != NULL; i++) {
        sscanf(split_string[i], "%c%d", &step->direction, &step->steps);
        index = index + (step->direction == 'R' ? 1 : -1);
        index = (index >= 0 ? index % 4 : 4 + (index % -4));
        current = (int *)aoc_ptr_array_index(directions, index);
        for (s = 0; s < step->steps; s++) {
            pos[0] = pos[0] + current[0];
            pos[1] = pos[1] + current[1];
            if (part_two) {
                char *check_key = strdup_printf("(%d, %d)", pos[0], pos[1]);
                if (g_hash_table_contains(locations, check_key)) {
                    int return_value = abs(pos[0]) + abs(pos[1]);
                    aoc_free(pos);
                    aoc_free(step);
                    aoc_free(check_key);
                    aoc_str_freev(split_string);
                    aoc_array_free(directions, true);

                    g_hash_table_destroy(locations);

                    return return_value;
                }
                g_hash_table_add(locations, check_key);
            }
        }
    }
    int return_value = abs(pos[0]) + abs(pos[1]);
    aoc_free(pos);
    aoc_free(step);
    aoc_str_freev(split_string);
    aoc_array_free(directions, true);

    g_hash_table_destroy(locations);
    return return_value;
}

void *solve_part_1(AocData_t *data) {
    return strdup_printf("%d", solution(aoc_data_get(data), FALSE));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%d", solution(aoc_data_get(data), TRUE));
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
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
