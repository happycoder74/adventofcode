#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t prio(char c) {
    if (isupper(c))
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
        char    *pack1 = (char *)aoc_calloc(pack_length + 1, sizeof(char));
        char    *pack2 = (char *)aoc_calloc(pack_length + 1, sizeof(char));

        memcpy(pack1, row, pack_length * sizeof(char));
        pack1[pack_length] = '\0';
        memcpy(pack2, row + pack_length, pack_length * sizeof(char));
        pack2[pack_length] = '\0';

        char **packs = (char **)aoc_calloc(2, sizeof(char *));

        packs[0] = pack1;
        packs[1] = pack2;

        aoc_ptr_array_append(rucksacks, packs);
    }

    aoc_array_free(data, data->free_segments);
    return rucksacks;
}

void *solve_part_1(AocData_t *data) {
    char **packs = NULL;

    int prio_sum = 0;
    for (uint16_t i = 0; i < aoc_data_length(data); i++) {
        packs = aoc_ptr_array_index(aoc_data_get(data), i);
        AocArrayPtr common_items = aoc_array_sized_new(AOC_ARRAY_CHAR, 20);
        for (uint16_t j = 0; j < strlen(packs[0]); j++) {
            if (strchr(packs[1], packs[0][j]) != NULL) {
                if (!aoc_char_array_contains(common_items, packs[0][j]))
                    aoc_char_array_append(common_items, packs[0][j]);
            }
        }

        for (uint16_t c = 0; c < aoc_array_length(common_items); c++) {
            prio_sum += prio(aoc_char_array_index(common_items, c));
        }
        aoc_char_array_free(common_items);
    }
    return strdup_printf("%d", prio_sum);
}

void *solve_part_2(AocData_t *data) {
    AocArrayPtr groups = aoc_ptr_array_new();
    AocArrayPtr group = aoc_ptr_array_new();

    for (uint32_t i = 0; i < aoc_data_length(data); i++) {
        char **packs = aoc_ptr_array_index(aoc_data_get(data), i);
        char  *pack = str_join("", packs, 2);
        aoc_ptr_array_append(group, pack);
        if ((((i + 1) % 3) == 0) && (i > 0)) {
            aoc_ptr_array_append(groups, group);
            group = aoc_ptr_array_new();
        }
    }

    int prio_sum = 0;

    for (uint32_t i = 0; i < aoc_array_length(groups); i++) {
        group = aoc_ptr_array_index(groups, i);
        char       *str = aoc_str_array_index(group, 0);
        AocArrayPtr common_items = aoc_char_array_new();

        char *str1 = aoc_str_array_index(group, 1);
        for (uint32_t k = 0; k < strlen(str); k++) {
            if (strchr(str1, str[k]) != NULL) {
                if (!aoc_char_array_contains(common_items, str[k]))
                    aoc_char_array_append(common_items, str[k]);
            }
        }
        str1 = aoc_str_array_index(group, 2);
        for (uint32_t k = 0; k < aoc_array_length(common_items); k++) {
            char item = aoc_char_array_index(common_items, k);
            if (!strchr(str1, item)) {
                int index = aoc_char_array_find(common_items, item);
                aoc_array_remove_index(common_items, index);
                k -= 1;
            }
        }

        prio_sum += prio(aoc_char_array_index(common_items, 0));
        aoc_char_array_free(common_items);
    }
    for (uint32_t group = 0; group < aoc_array_length(groups); group++) {
        AocArrayPtr group_ptr = aoc_ptr_array_index(groups, group);
        aoc_array_free(group_ptr, group_ptr->free_segments);
    }
    aoc_array_free(groups, 0);
    return strdup_printf("%d", prio_sum);
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

    for (uint32_t segment = 0; segment < aoc_data_length(data); segment++) {
        char **packs = (char **)aoc_ptr_array_index(data->data, segment);
        aoc_free(packs[0]);
        aoc_free(packs[1]);
    }
    aoc_data_free(data);

    return aoc_mem_gc();
}
