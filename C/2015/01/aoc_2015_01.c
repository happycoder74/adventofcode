#include "glib.h"
#include <stdio.h>
#include <string.h>

#include "aoc_utils.h"
#include "aoc_timer.h"

gpointer solve_part_1(AocData_t *data) {
    int level = 0;
    int i = 0;
    char *line;

    line = g_array_index(data->data, char *, i);

    for (i = 0; i < (int)strlen(line); i++) {
        if (line[i] == '(')
            level += 1;
        else if (line[i] == ')')
            level -= 1;
    }
    return (gpointer)g_strdup_printf("%d", level);
}

gpointer solve_part_2(AocData_t *data) {
    int i = 0;
    int level = 0;

    char *line;

    line = g_array_index(data->data, char *, i);
    for (i = 0; i < (int)strlen(line); i++) {
        if (line[i] == '(')
            level += 1;
        else if (line[i] == ')')
            level -= 1;
        if (level < 0)
            return (gpointer)g_strdup_printf("%d", i + 1);
    }
    return NULL;
}

gpointer solve_all(AocData_t *data) {

    data->data = get_input(data->filename, data->year, data->day);
    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    gchar *filename;

    if (argc > 1)
        filename = g_strdup(argv[1]);
    else
        filename = g_strdup("input.txt");

    data = aoc_data_new(filename, 2015, 1);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);
}
