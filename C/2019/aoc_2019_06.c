#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t count_direct(AocHashTable *table, char *key) {
    AocArrayPtr data = aoc_hash_table_lookup(table, key);
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
    AocHashTable *table = aoc_hash_table_create_custom(0, NULL, free, free, AOC_STR);

    AocArrayPtr lines = aoc_data_get(data);
    for (uint32_t i = 0; i < lines->length; i++) {
        char  *line = aoc_str_array_index(lines, i);
        char **line_split = str_split(line, ")", 0);
        char  *delimiter = strstr(line, ")");
        char  *orb = strndup(line, delimiter - line);
        char  *orbit = line_split[1];

        AocArrayPtr orbiters = aoc_hash_table_lookup(table, orb);

        if (orbiters) {
            aoc_str_array_append(orbiters, orbit);
        } else {
            AocArrayPtr orbiters = aoc_str_array_new();
            aoc_str_array_append(orbiters, orbit);
            aoc_hash_table_insert(table, orb, orbiters);
        }
        free(line_split);
    }

    uint32_t direct_count = count_direct(table, "COM");
    uint32_t indirect_count = 0;

    AocHashIterator iter;
    void           *key, *value;
    aoc_hash_table_iter_init(&iter, table);
    while (aoc_hash_table_iter_next(&iter, &key, &value)) {
        char *name = key;
        if (strcmp(name, "COM") != 0) {
            indirect_count += count_direct(table, name);
        }
    }

    aoc_hash_table_destroy(&table);
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

    const unsigned year = 2019;
    const unsigned day = 6;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
