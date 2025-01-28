#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_header.h"
#include "aoc_stack.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *opening[] = {"(", "[", "{", "<"};
char *closing[] = {")", "]", "}", ">"};

#define aoc_int32_hash_table_lookup(_hashtable_, _key_)                                            \
    *(int32_t *)aoc_hash_table_lookup(_hashtable_, _key_)

AocHashTable *init_brackets(void) {
    AocHashTable *brackets;
    brackets = aoc_hash_table_create(AOC_STR);

    for (unsigned i = 0; i < 4; i++) {
        aoc_hash_table_insert(brackets, opening[i], closing[i]);
    }

    return brackets;
}

AocHashTable *init_points(const int *point_array) {
    AocHashTable *points;
    points = aoc_hash_table_create(AOC_STR);
    for (unsigned i = 0; i < 4; i++) {
        aoc_hash_table_insert(points, closing[i], (void *)(&point_array[i]));
    }
    return points;
}

void *solve_part_1(AocData_t *data) {
    AocStack     *stack;
    AocHashTable *brackets, *points;
    char         *line;
    int           error_points = 0;
    const int     point_array[] = {3, 57, 1197, 25137};

    brackets = init_brackets();
    points = init_points(point_array);

    for (unsigned int j = 0; j < aoc_data_length(data); j++) {
        stack = aoc_stack_new();
        line = aoc_str_array_index(aoc_data_get(data), j);
        for (unsigned int i = 0; i < strlen(line); i++) {
            char *key = strdup_printf("%c", line[i]);
            char *last_bracket;
            if (aoc_hash_table_lookup(brackets, key)) {
                aoc_stack_push(stack, key);
            } else {
                last_bracket = aoc_stack_peek(stack);
                char *lookup_bracket = (char *)aoc_hash_table_lookup(brackets, last_bracket);
                if (strcmp(key, lookup_bracket)) {
                    error_points += *(int *)(aoc_hash_table_lookup(points, key));
                    break;
                } else {
                    last_bracket = aoc_stack_pop(stack);
                }
                free(key);
            }
        }
        aoc_stack_free(stack);
    }
    aoc_hash_table_destroy(&brackets);
    aoc_hash_table_destroy(&points);
    return strdup_printf("%d", error_points);
}

void *solve_part_2(AocData_t *data) {
    AocStack     *stack;
    AocHashTable *brackets, *points;
    char         *line;
    int8_t        valid;
    char         *key;
    char         *last_bracket;
    int64_t       complete_points;
    AocArrayPtr   result;
    const int     point_array[] = {1, 2, 3, 4};

    brackets = init_brackets();
    points = init_points(point_array);

    result = aoc_int64_array_new();
    for (unsigned int j = 0; j < aoc_data_length(data); j++) {
        complete_points = 0;
        valid = TRUE;
        stack = aoc_stack_new();
        line = aoc_str_array_index(aoc_data_get(data), j);
        for (unsigned int i = 0; i < strlen(line); i++) {
            key = strdup_printf("%c", line[i]);
            if (aoc_hash_table_lookup(brackets, key)) {
                aoc_stack_push(stack, key);
            } else {
                last_bracket = aoc_stack_peek(stack);
                if (strcmp(key, (char *)aoc_hash_table_lookup(brackets, last_bracket))) {
                    valid = FALSE;
                    break;
                } else {
                    last_bracket = aoc_stack_pop(stack);
                }
            }
        }
        if (valid) {
            while ((last_bracket = aoc_stack_pop(stack))) {
                complete_points *= 5;
                complete_points += aoc_int32_hash_table_lookup(
                    points, aoc_hash_table_lookup(brackets, last_bracket));
            }
            aoc_int64_array_append(result, complete_points);
        }
        aoc_stack_free(stack);
    }
    aoc_hash_table_destroy(&brackets);
    aoc_hash_table_destroy(&points);
    aoc_int64_array_sort(result, int64_compare);

    return strdup_printf("%lld", aoc_int64_array_index(result, aoc_array_length(result) / 2));
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func_bench(1, solve_part_1, data, 1, 0, 100);
        timer_func_bench(2, solve_part_2, data, 1, 0, 100);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2021;
    const unsigned day = 10;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
