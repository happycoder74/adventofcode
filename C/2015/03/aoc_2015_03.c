#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

GArray *clean_input(GArray *data) {
    return data;
}

void point_destroy(gpointer data) {
    g_free(data);
}

int solver(GArray *data, guint agents) {
    gchar *line;
    GHashTable *visited;
    Point *position;
    guint visited_size;
    guint position_index = 0;
    Point *key;

    position = calloc(agents, sizeof(Point));
    visited = g_hash_table_new_full(point_hash, point_equal, point_destroy, NULL);

    key = g_new0(Point, 1);
    key->x = position[position_index].x;
    key->y = position[position_index].y;
    g_hash_table_add(visited, key);

    line = g_array_index(data, gchar *, 0);
    for (guint c = 0; c < strlen(line); c++) {
        position_index = c % agents;
        switch(line[c]) {
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
        key = g_new0(Point, 1);
        key->x = position[position_index].x;
        key->y = position[position_index].y;
        g_hash_table_add(visited, key);
    }
    visited_size = g_hash_table_size(visited);

    g_free(position);
    g_hash_table_destroy(visited);
    return visited_size;

}
int solve_part_1(GArray *data) {
    return solver(data, 1);
}

int solve_part_2(GArray *data) {
    return solver(data, 2);
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = clean_input(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), INT, 1);

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

    TIMER(0, solve_all(filename, 2015, 3), INT, 0);
    g_free(filename);
}
