#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include "glibconfig.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

GHashTable *init_brackets(void) {
    GHashTable *brackets;
    brackets = g_hash_table_new(g_direct_hash, g_direct_equal);

    g_hash_table_insert(brackets, GUINT_TO_POINTER('('), GUINT_TO_POINTER(')'));
    g_hash_table_insert(brackets, GUINT_TO_POINTER('['), GUINT_TO_POINTER(']'));
    g_hash_table_insert(brackets, GUINT_TO_POINTER('{'), GUINT_TO_POINTER('}'));
    g_hash_table_insert(brackets, GUINT_TO_POINTER('<'), GUINT_TO_POINTER('>'));

    return brackets;
}

GHashTable *init_points(const int *point_array) {
    GHashTable *points;
    points = g_hash_table_new(g_direct_hash, g_direct_equal);
    g_hash_table_insert(points, GUINT_TO_POINTER(')'), GUINT_TO_POINTER(point_array[0]));
    g_hash_table_insert(points, GUINT_TO_POINTER(']'), GUINT_TO_POINTER(point_array[1]));
    g_hash_table_insert(points, GUINT_TO_POINTER('}'), GUINT_TO_POINTER(point_array[2]));
    g_hash_table_insert(points, GUINT_TO_POINTER('>'), GUINT_TO_POINTER(point_array[3]));

    return points;
}

static void queue_free_function(void *ptr) {
    free(ptr);
}

void *solve_part_1(AocData_t *data) {
    GQueue     *stack;
    GHashTable *brackets, *points;
    char       *line;
    int         error_points = 0;
    const int   point_array[] = {3, 57, 1197, 25137};

    brackets = init_brackets();
    points = init_points(point_array);

    for (unsigned int j = 0; j < aoc_data_length(data); j++) {
        stack = g_queue_new();
        line = aoc_str_array_index(aoc_data_get(data), j);
        for (unsigned int i = 0; i < strlen(line); i++) {
            char key = line[i];
            char last_bracket;
            if (g_hash_table_contains(brackets, GUINT_TO_POINTER(key))) {
                g_queue_push_tail(stack, GUINT_TO_POINTER(key));
            } else {
                last_bracket = GPOINTER_TO_UINT(g_queue_peek_tail(stack));
                char lookup_bracket = GPOINTER_TO_UINT(g_hash_table_lookup(brackets, GUINT_TO_POINTER(last_bracket)));
                if (key != lookup_bracket) {
                    int localpoints = (int)(int64_t)(g_hash_table_lookup(points, (void *)(guint64)key));
                    error_points += localpoints;
                    break;
                } else {
                    last_bracket = (guint)(guint64)g_queue_pop_tail(stack);
                }
            }
        }
        g_queue_free(stack);
    }
    g_hash_table_destroy(brackets);
    g_hash_table_destroy(points);
    return strdup_printf("%d", error_points);
}

static int int64_compare(const void *a, const void *b) {
    int64_t v_a = *(int64_t *)a;
    int64_t v_b = *(int64_t *)b;

    if (v_a == v_b) {
        return 0;
    } else {
        return (int)((v_a - v_b) / (llabs(v_a - v_b)));
    }
}

void *solve_part_2(AocData_t *data) {
    GQueue     *stack;
    GHashTable *brackets, *points;
    char       *line;
    int8_t      valid;
    char        last_bracket;
    int64_t     complete_points;
    AocArrayPtr result;
    const int   point_array[] = {1, 2, 3, 4};

    brackets = init_brackets();
    points = init_points(point_array);

    result = aoc_int64_array_new();
    for (unsigned int j = 0; j < aoc_data_length(data); j++) {
        complete_points = 0;
        valid = TRUE;
        stack = g_queue_new();
        line = aoc_str_array_index(aoc_data_get(data), j);
        for (unsigned int i = 0; i < strlen(line); i++) {
            char key = line[i];
            if (g_hash_table_contains(brackets, GUINT_TO_POINTER(key))) {
                g_queue_push_tail(stack, GUINT_TO_POINTER(key));
            } else {
                last_bracket = GPOINTER_TO_UINT(g_queue_peek_tail(stack));
                if (key != last_bracket) {
                    valid = FALSE;
                    break;
                } else {
                    last_bracket = GPOINTER_TO_UINT(g_queue_pop_tail(stack));
                }
            }
        }
        if (valid) {
            while ((last_bracket = GPOINTER_TO_UINT(g_queue_pop_tail(stack)))) {
                complete_points = complete_points * 5 + (int64_t)(g_hash_table_lookup(points, g_hash_table_lookup(brackets, GUINT_TO_POINTER(last_bracket))));
            }
            aoc_int64_array_append(result, complete_points);
        }
        g_queue_free(stack);
    }
    g_hash_table_destroy(brackets);
    g_hash_table_destroy(points);
    aoc_int64_array_sort(result, int64_compare);
    int64_t return_value = aoc_int64_array_index(result, aoc_array_length(result) / 2);
    aoc_int64_array_free(result);

    return strdup_printf("%lld", return_value);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        // timer_func(1, solve_part_1, data, 1);
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

    return 0;
}
