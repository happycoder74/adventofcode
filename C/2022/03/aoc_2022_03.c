#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc_string.h"
#include "aoc_utils.h"
#include "aoc_timer.h"
#include "aoc_array.h"
#include "aoc_sets.h"

int32_t prio(char c) {
    if(isupper(c))
        return c - 'A' + 27;
    return c - 'a' + 1;
}

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr rucksacks;
    rucksacks = aoc_ptr_array_new();
    for (uint32_t i = 0; i < aoc_array_length(data); i++) {
        char *row = aoc_str_array_index(data, i);
        row = str_trim(row);
        uint16_t pack_length = strlen(row) / 2;
        char *pack1 = (char *)calloc(pack_length + 1, sizeof(char));
        char *pack2 = (char *)calloc(pack_length + 1, sizeof(char));

        char *ptr = row + (pack_length);
        strncpy(pack1, row, pack_length);
        strncpy(pack2, ptr, pack_length);

        char **packs = (char **)calloc(2, sizeof(char *));

        packs[0] = pack1;
        packs[1] = pack2;

        aoc_ptr_array_append(rucksacks, packs);
    }

    aoc_str_array_free(data);
    return rucksacks;
}

void *solve_part_1(AocData_t *data) {
    char **packs = NULL;

    int prio_sum = 0;
    for (uint16_t i = 0; i < aoc_data_length(data); i++) {
        packs = aoc_ptr_array_index(aoc_data_get(data), i);
        GHashTable *common_items = g_hash_table_new(g_direct_hash, g_direct_equal);
        for (uint16_t j = 0; j < strlen(packs[0]); j++) {
            if(strchr(packs[1], packs[0][j]) != NULL) {
                g_hash_table_insert(common_items, GINT_TO_POINTER(packs[0][j]), GINT_TO_POINTER(packs[0][j]));
            }
        }

        uint32_t table_size;
        void **keys = g_hash_table_get_keys_as_array(common_items, &table_size);
        for (uint16_t c = 0; c < table_size; c++) {
            char item = GPOINTER_TO_INT(g_hash_table_lookup(common_items, keys[c]));
            prio_sum += prio(item);
        }
    }
    return strdup_printf("%d", prio_sum);
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
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new_clean("test_input.txt", year, day, clean_input);
        } else {
            data = aoc_data_new_clean(argv[1], year, day, clean_input);
        }
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}


