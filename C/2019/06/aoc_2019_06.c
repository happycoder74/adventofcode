#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include "glib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t count_direct(GHashTable *table, char *key) {
    AocArrayPtr data = g_hash_table_lookup(table, key);
    if (!data) {
        return 0;
    }

    uint32_t sum_of_rest = 0;
    for (size_t i = 0; i < data->length; i++) {
        char *key2 = aoc_str_array_index(data, i);
        sum_of_rest += count_direct(table, key2);
    }
    return data->length + sum_of_rest;
}

void *solve_part_1(AocData_t *data) {
    GHashTable *table = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);

    AocArrayPtr lines = aoc_data_get(data);
    for (uint32_t i = 0; i < lines->length; i++) {
        char  *line = aoc_str_array_index(lines, i);
        char **line_split = g_strsplit(line, ")", 0);
        char  *delimiter = strstr(line, ")");
        char  *orb = strndup(line, delimiter - line);
        char  *orbit = line_split[1];

        AocArrayPtr orbiters = g_hash_table_lookup(table, orb);

        if (orbiters) {
            aoc_str_array_append(orbiters, orbit);
        } else {
            AocArrayPtr orbiters = aoc_str_array_new();
            aoc_str_array_append(orbiters, orbit);
            g_hash_table_insert(table, orb, orbiters);
        }
        free(line_split);
    }

    uint32_t direct_count = count_direct(table, "COM");
    uint32_t indirect_count = 0;

    uint32_t length;
    char   **keys = (char **)g_hash_table_get_keys_as_array(table, &length);
    for (uint32_t i = 0; i < length; i++) {
        char *name = keys[i];
        if (strcmp(name, "COM") != 0) {
            indirect_count += count_direct(table, name);
        }
    }

    free(keys);
    g_hash_table_destroy(table);
    return strdup_printf("%u", direct_count + indirect_count);
}

void *solve_part_2(AocData_t *data) {
    return NULL;
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
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
            data = aoc_data_new_clean("test_input.txt", year, day, NULL);
        } else {
            data = aoc_data_new_clean(argv[1], year, day, NULL);
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
