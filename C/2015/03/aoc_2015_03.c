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

gpointer solve_part_1(AocData_t *data) {
    return g_strdup_printf("%d", solver(data->data, 1));
}

gpointer solve_part_2(AocData_t *data) {
    return g_strdup_printf("%d", solver(data->data, 2));
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

    const int year = 2015;
    const int day = 3;
    if (argc > 1)
        filename = g_strdup(argv[1]);
    else
        filename = g_strdup("input.txt");

    data = aoc_data_new(filename, year, day);
    g_free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);
}
