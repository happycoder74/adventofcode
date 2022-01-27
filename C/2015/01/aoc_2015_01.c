#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "aoc_utils.h"

int solve_part_1(GArray *data) {
    int level = 0;
    int i = 0;
    char *line;

    line = g_array_index(data, char *, i);

    for (i = 0; i < (int)strlen(line); i++) {
        if (line[i] == '(')
            level += 1;
        else if (line[i] == ')')
            level -= 1;
    }
    return level;
}

int solve_part_2(GArray *data) {
    int i = 0;
    int level = 0;

    char *line;

    line = g_array_index(data, char *, i);
    for (i = 0; i < (int)strlen(line); i++) {
        if (line[i] == '(')
            level += 1;
        else if (line[i] == ')')
            level -= 1;
        if (level < 0) return i + 1;
    }
    return 0;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = get_input(filename, year, day);
    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), INT, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}
int main(int argc, char **argv) {
    char *filename;

    if (argc > 1)
        filename = argv[1];
    else
        filename = g_strdup("input.txt");

    TIMER(0, solve_all(filename, 2015, 1), INT, 0);
    g_free(filename);
}
