#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include "aoc_string.h"

GArray *clean_input(GArray *data) {
    return data;
}

gint marker(GArray *data, unsigned int window) {
    unsigned int i, j;
    char *string;
    char *chunk;

    chunk = (char *)calloc((size_t)window + 1, sizeof(char));
    string = g_array_index(data, char *, 0);
    for (i = 0; i < strlen(string) - window; i++) {
        chunk[0] = '\0';
        for (j = 0; j < window; j++) {
            if(strchr(chunk, string[i + j])) {
                break;
            } else {
                chunk[j] = string[i + j];
                chunk[j + 1] = '\0';
            }
            if (strlen(chunk) == window) {
                free(chunk);
                return i + window;
            }
        }
    }
    free(chunk);


    return 0;

}
void *solve_part_1(AocData_t *data) {
    return strdup_printf("%d", marker(data->data, 4));
}

void *solve_part_2(AocData_t *data) {
    return strdup_printf("%d", marker(data->data, 14));
}

void *solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, 2022, 6);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
