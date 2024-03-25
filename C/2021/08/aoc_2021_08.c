#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_hash.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr result;
    size_t      i;
    char      **split_line;

    result = aoc_ptr_array_new();
    for (i = 0; i < aoc_array_length(data); i++) {
        split_line = aoc_str_split(aoc_str_array_index(data, i), "|", 0);
        aoc_ptr_array_append(result, split_line);
    }

    // Note we do not free split line here, since the memory is used in the new array.
    aoc_str_array_free(data);
    return result;
}

static int aoc_hash_table_set_compare(AocHashTable *a, AocHashTable *b) {
    AocHashIterator iter;
    void           *key, *value;

    if (aoc_hash_table_count(a) != aoc_hash_table_count(b)) {
        return false;
    }

    aoc_hash_table_iter_init(&iter, a);
    while (aoc_hash_table_iter_next(&iter, &key, &value)) {
        if (!aoc_hash_table_contains(b, key)) {
            return false;
        }
    }
    return true;
}

static int aoc_hash_table_set_difference(AocHashTable *a, AocHashTable *b) {
    int             diff_size;
    AocHashIterator iter;
    void           *key, *value;

    diff_size = aoc_hash_table_count(a);
    aoc_hash_table_iter_init(&iter, a);
    while (aoc_hash_table_iter_next(&iter, &key, &value)) {
        if (aoc_hash_table_contains(b, key)) {
            diff_size -= 1;
        }
    }
    return diff_size >= 0 ? diff_size : 0;
}

static int aoc_hash_table_set_intersection(AocHashTable *a, AocHashTable *b) {
    size_t          common_keys = 0;
    AocHashIterator iter;
    void           *key, *value;

    aoc_hash_table_iter_init(&iter, a);
    while (aoc_hash_table_iter_next(&iter, &key, &value)) {
        if (aoc_hash_table_contains(b, key)) {
            common_keys += 1;
        }
    }
    return common_keys;
}

int signal_sort(const void *a, const void *b) {
    const char *str1 = *((char **)a);
    const char *str2 = *((char **)b);

    return strlen(str1) - strlen(str2);
}

AocHashTable **decode_signal(char *signal) {
    int           signal_set_key[10] = {0};
    AocArrayPtr   signal_sets;
    char        **parts;
    AocHashTable *set;
    AocArrayPtr   signal_parts;
    char         *letter_key;

    signal_set_key[1] = 0;
    signal_set_key[7] = 1;
    signal_set_key[4] = 2;
    signal_set_key[8] = 9;

    signal_sets = aoc_ptr_array_new();
    signal_parts = aoc_str_array_new();
    parts = aoc_str_split(str_trim(signal), " ", 0);
    size_t j = 0;
    while (parts[j] != NULL) {
        aoc_str_array_append(signal_parts, parts[j]);
        j++;
    }

    aoc_str_array_sort(signal_parts, signal_sort);

    for (j = 0; j < aoc_array_length(signal_parts); j++) {
        set = aoc_hash_table_create_custom(0, NULL, free, NULL, AOC_CHAR);
        char *part = aoc_str_array_index(signal_parts, j);
        for (size_t k = 0; k < strlen(part); k++) {
            letter_key = (char *)malloc(sizeof(char));
            *letter_key = part[k];
            aoc_hash_table_add(set, letter_key);
        }
        aoc_ptr_array_append(signal_sets, set);
    }
    for (size_t i = 0; i < aoc_array_length(signal_sets); i++) {
        set = (AocHashTable *)aoc_ptr_array_index(signal_sets, i);
        if (aoc_hash_table_count(set) == 5) {
            if (aoc_hash_table_set_intersection(set, (AocHashTable *)aoc_ptr_array_index(
                                                         signal_sets, signal_set_key[1])) == 2) {
                signal_set_key[3] = i;
            } else if (aoc_hash_table_set_intersection(set, (AocHashTable *)aoc_ptr_array_index(
                                                                signal_sets, signal_set_key[4])) ==
                       2) {
                signal_set_key[2] = i;
            } else {
                signal_set_key[5] = i;
            }
        } else if (aoc_hash_table_count(set) == 6) {
            if (aoc_hash_table_set_difference(set, (AocHashTable *)aoc_ptr_array_index(
                                                       signal_sets, signal_set_key[4])) == 2) {
                signal_set_key[9] = i;
            } else if (aoc_hash_table_set_difference(set, (AocHashTable *)aoc_ptr_array_index(
                                                              signal_sets, signal_set_key[5])) ==
                       2) {
                signal_set_key[0] = i;
            } else {
                signal_set_key[6] = i;
            }
        }
    }

    AocHashTable **decoded;
    decoded = (AocHashTable **)calloc(10, sizeof(AocHashTable *));
    for (size_t hkey = 0; hkey < 10; hkey++) {
        decoded[hkey] = (AocHashTable *)aoc_ptr_array_index(signal_sets, signal_set_key[hkey]);
    }

    return decoded;
}

AocArrayPtr decode(AocHashTable **keys, char *signal) {
    AocArrayPtr   message;
    char        **parts;
    AocArrayPtr   signal_sets;
    AocHashTable *signal_set;
    AocHashTable *set;

    parts = aoc_str_split(str_trim(signal), " ", 0);
    signal_sets = aoc_ptr_array_new();
    message = aoc_int32_array_new();

    size_t j = 0;
    while (parts[j] != NULL) {
        set = aoc_hash_table_create(AOC_CHAR);
        for (size_t k = 0; k < strlen(parts[j]); k++) {
            aoc_hash_table_add(set, &parts[j][k]);
        }
        aoc_ptr_array_append(signal_sets, set);
        j++;
    }
    for (size_t i = 0; i < aoc_array_length(signal_sets); i++) {
        // This is the decoding loop, where the signal is compared to the keys in the
        // decoded list of hash_tables. Again not really sure this is the best way to do this.
        signal_set = (AocHashTable *)aoc_ptr_array_index(signal_sets, i);
        for (size_t j = 0; j < 10; j++) {
            set = keys[j];
            if (aoc_hash_table_set_compare(set, signal_set)) {
                aoc_int_array_append(message, j);
            }
        }
    }

    aoc_str_freev(parts);

    return message;
}

void *solve_part_1(AocData_t *data) {
    char **split_line;
    char **output_value;
    char  *val;
    int    count = 0;

    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_ptr_array_index(aoc_data_get(data), i);
        output_value = aoc_str_split(str_trim(split_line[1]), " ", 0);

        int j = 0;
        while ((val = output_value[j]) != NULL) {
            if ((strlen(val) >= 2 && strlen(val) <= 4) || strlen(val) == 7) {
                count++;
            }
            j++;
        }
    }
    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    char         **split_line;
    int            array_sum;
    AocHashTable **decoded;
    AocArrayPtr    message;
    int            message_sum;

    array_sum = 0;
    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_ptr_array_index(aoc_data_get(data), i);
        decoded = decode_signal(str_trim(split_line[0]));
        message = decode(decoded, str_trim(split_line[1]));
        message_sum = 0;
        for (size_t j = 0; j < aoc_array_length(message); j++) {
            message_sum += (int)pow((double)10, (double)(3 - j)) * aoc_int_array_index(message, j);
        }

        array_sum += message_sum;
        free(split_line[0]);
        free(split_line[1]);
        free(decoded);
    }

    return strdup_printf("%d", array_sum);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2021;
    const unsigned day = 8;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
