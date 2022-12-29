#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

typedef struct {
    int id;
    GArray *items;
    char *operation;
    int *divisor;
    int if_true;
    int if_false;
} Monkey;


GArray *clean_input(GArray *data) {
    GArray *return_array = g_array_new(TRUE, FALSE, sizeof(Monkey *));
    gint i;
    Monkey *monkey;
    gchar *line;

    for (i = 0; i < data->len; i++) {
        line = g_strstrip(g_array_index(data, gchar *, i));
        if (strlen(line) > 0) {
            if (str_startswith(line, "Monkey")) {
                monkey = g_new(Monkey, 1);
                sscanf(line, "Monkey %d:", &monkey->id);
                printf("Adding Monkey %d\n", monkey->id);
                g_array_append_val(return_array, monkey);
            } else if (str_startswith(line, "Starting")) {
            }
        }
    }

    return return_array;
}

gpointer solve_part_1(AocData_t *data) {
    Monkey *monkey;
    gint i;

    for(i = 0; i < data->data->len; i++) {
        monkey = g_array_index(data->data, Monkey *, i);
        g_print("Monkey %d:\n", monkey->id);
    }
    return NULL;
}

gpointer solve_part_2(AocData_t *data) {
    return NULL;
}

gpointer solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = aoc_data_new(filename, 2022, 11);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
