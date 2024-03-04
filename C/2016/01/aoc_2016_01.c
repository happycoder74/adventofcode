#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solution(AocArrayPtr data, int part_two) {
    char **split_string;
    int    i;
    Point *pos;

    AocHashTable *locations = NULL;

    typedef struct {
        char direction;
        int  steps;
    } step_t;

    step_t *step = (step_t *)malloc(sizeof(step_t));
    locations = aoc_hash_table_create(AOC_KEY_POINT);

    Point directions[4] = {
        {1,  0 },
        {0,  1 },
        {-1, 0 },
        {0,  -1}
    };

    pos = point_new_m(0, 0);

    if (part_two) {
        Point *point = point_new_m(pos->x, pos->y);
        aoc_hash_table_add(locations, point);
    }
    split_string = aoc_str_split(aoc_str_array_index(data, 0), ", ", 0);
    int index = 0;
    int s = 0;
    for (i = 0; split_string[i] != NULL; i++) {
        sscanf(split_string[i], "%c%d", &step->direction, &step->steps);
        index = index + (step->direction == 'R' ? 1 : -1);
        index = (index >= 0 ? index % 4 : 4 + (index % -4));
        for (s = 0; s < step->steps; s++) {
            point_move(pos, directions[index]);
            if (part_two) {
                Point *check_key = point_new_m(pos->x, pos->y);
                if (aoc_hash_table_lookup(locations, check_key)) {
                    int return_value = abs(pos->x) + abs(pos->y);
                    free(pos);
                    free(step);
                    free(check_key);
                    aoc_str_freev(split_string);

                    aoc_hash_table_destroy(&locations);

                    return return_value;
                }
                aoc_hash_table_add(locations, check_key);
            }
        }
    }
    int return_value = abs(pos->x) + abs(pos->y);
    free(pos);
    free(step);
    aoc_str_freev(split_string);
    aoc_hash_table_destroy(&locations);
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

    const unsigned year = 2016;
    const unsigned day = 1;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
