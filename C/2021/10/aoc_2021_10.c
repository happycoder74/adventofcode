#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

GArray *clean_input(GArray *data) {
    return data;
}

GHashTable *init_brackets() {
    GHashTable *brackets;
    brackets = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(brackets, "(", ")");
    g_hash_table_insert(brackets, "[", "]");
    g_hash_table_insert(brackets, "{", "}");
    g_hash_table_insert(brackets, "<", ">");

    return brackets;
}

GHashTable *init_points(const int *point_array) {
    GHashTable *points;
    points = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(points, ")", GINT_TO_POINTER(point_array[0]));
    g_hash_table_insert(points, "]", GINT_TO_POINTER(point_array[1]));
    g_hash_table_insert(points, "}", GINT_TO_POINTER(point_array[2]));
    g_hash_table_insert(points, ">", GINT_TO_POINTER(point_array[3]));

    return points;
}

int solve_part_1(GArray *data) {
    GQueue *stack;
    GHashTable *brackets, *points;
    gchar *line;
    gint error_points = 0;
    const int point_array[] = {3, 57, 1197, 25137};

    brackets = init_brackets();
    points = init_points(point_array);

    for(guint j = 0; j < data->len; j++) {
        stack = g_queue_new();
        line = g_array_index(data, gchar *, j);
        for(guint i = 0; i < strlen(line); i++) {
            gchar *key = g_strdup_printf("%c", line[i]);
            gchar *last_bracket;
            if (g_hash_table_contains(brackets, key)) {
                g_queue_push_tail(stack, key);
            } else {
                last_bracket = g_queue_peek_tail(stack);
                if(strcmp(key, (gchar *)g_hash_table_lookup(brackets, last_bracket))) {
                    error_points += GPOINTER_TO_INT(g_hash_table_lookup(points, key));
                    break;
                } else {
                    last_bracket = g_queue_pop_tail(stack);
                }
            }
        }
        g_queue_free_full(stack, g_free);
    }
    g_hash_table_destroy(brackets);
    g_hash_table_destroy(points);
    return error_points;
}

static gint long_compare(gconstpointer a, gconstpointer b) {
    long v_a = *(long *)a;
    long v_b = *(long *)b;

    if (v_a == v_b) {
        return 0;
    } else {
        return (gint)((v_a - v_b) / (labs(v_a - v_b)));

    }
}

long solve_part_2(GArray *data) {
    GQueue *stack;
    GHashTable *brackets, *points;
    gchar *line;
    gboolean valid;
    gchar *key;
    gchar *last_bracket;
    glong complete_points;
    GArray *result;
    const int point_array[] = {1, 2, 3, 4};


    brackets = init_brackets();
    points = init_points(point_array);

    result = g_array_new(FALSE, FALSE, sizeof(glong));
    for(guint j = 0; j < data->len; j++) {
        complete_points = 0;
        valid = TRUE;
        stack = g_queue_new();
        line = g_array_index(data, gchar *, j);
        for(guint i = 0; i < strlen(line); i++) {
            key = g_strdup_printf("%c", line[i]);
            if (g_hash_table_contains(brackets, key)) {
                g_queue_push_tail(stack, key);
            } else {
                last_bracket = g_queue_peek_tail(stack);
                if(strcmp(key, (gchar *)g_hash_table_lookup(brackets, last_bracket))) {
                    valid = FALSE;
                    break;
                } else {
                    last_bracket = g_queue_pop_tail(stack);
                }
            }
        }
        if (valid) {
            while ((last_bracket = g_queue_pop_tail(stack))) {
                complete_points = complete_points * 5 + GPOINTER_TO_INT(g_hash_table_lookup(points, g_hash_table_lookup(brackets, last_bracket)));
            }
            g_array_append_val(result, complete_points);
        }
        g_queue_free_full(stack, g_free);
    }
    g_hash_table_destroy(brackets);
    g_hash_table_destroy(points);
    g_array_sort(result, long_compare);

    return g_array_index(result, long, result->len / 2);
}

long solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = clean_input(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), LONG, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2021, 10), INT, 0);
    g_free(filename);
}
