#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "aoc_utils.h"

int solve_part_1(GArray *data) {
    int level = 0;
    int i = 0;
    char *line;

    line = g_array_index(data, char *, i);

    for (i = 0; i < strlen(line); i++) {
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
    for (i = 0; i < strlen(line); i++) {
        if (line[i] == '(')
            level += 1;
        else if (line[i] == ')')
            level -= 1;
        if (level < 0) return i + 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    GArray *data;
    char *filename;

    if (argc > 1)
        filename = argv[1];
    else
        filename = g_strdup("input.txt");

    data = get_input(filename, 2015, 1);
    if (data) {
        TIMER_INT(1, solve_part_1(data));
        TIMER_INT(2, solve_part_2(data));

        g_array_free(data, TRUE);
    }
    g_free(filename);
}
