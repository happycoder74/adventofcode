#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glib.h>
#include "aoc_array.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"

#ifndef NDEBUG
#include "aoc_mem.h"
#endif

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr result;
    size_t i;
    char **split_line;

    result = aoc_ptr_array_new();
    for (i = 0; i < aoc_array_length(data); i++) {
        split_line = aoc_str_split(aoc_str_array_index(data, i), "|", -1);
        aoc_ptr_array_append(result, split_line);
    }

    // Note we do not free split line here, since the memory is used in the new array.
    for(size_t index = 0; index < aoc_array_length(data); index++) {
        char *str = aoc_str_array_index(data, index);
        free(str);
    }
    aoc_array_free(data, 0);
    return result;
}

static int g_hash_table_set_compare(GHashTable *a, GHashTable *b) {
    GHashTableIter iter;
    void *key, *value;

    if (g_hash_table_size(a) != g_hash_table_size(b))
        return FALSE;

    g_hash_table_iter_init(&iter, a);
    while(g_hash_table_iter_next(&iter, &key, &value)) {
        if(!g_hash_table_contains(b, key)) {
            return FALSE;
        }
    }
    return TRUE;
}

static int g_hash_table_set_difference(GHashTable *a, GHashTable *b) {
    int diff_size;
    GHashTableIter iter;
    void *key, *value;

    diff_size = g_hash_table_size(a);
    g_hash_table_iter_init(&iter, a);
    while(g_hash_table_iter_next(&iter, &key, &value)) {
        if(g_hash_table_contains(b, key))
            diff_size -= 1;
    }
    return diff_size >= 0 ? diff_size : 0;
}

static int g_hash_table_set_intersection(GHashTable *a, GHashTable *b) {
    size_t common_keys = 0;
    GHashTableIter iter;
    void *key, *value;

    g_hash_table_iter_init(&iter, a);
    while(g_hash_table_iter_next(&iter, &key, &value)) {
        if(g_hash_table_contains(b, key))
            common_keys += 1;
    }
    return common_keys;
}

int signal_sort(const void *a, const void *b) {
    const char *str1 = *((char **) a);
    const char *str2 = *((char **) b);

    return strlen(str1) - strlen(str2);
}

GHashTable **decode_signal(char *signal) {
    int *signal_set_key;
    AocArrayPtr signal_sets;
    char **parts;
    GHashTable *set;
    AocArrayPtr signal_parts;
    char letter_key;

    signal_set_key = (int *)calloc(10, sizeof(int));
    signal_set_key[1] = 0;
    signal_set_key[7] = 1;
    signal_set_key[4] = 2;
    signal_set_key[8] = 9;

    signal_sets = aoc_ptr_array_new();
    signal_parts = aoc_str_array_new();
    parts = aoc_str_split(str_trim(signal), " ", -1);
    size_t j = 0;
    while (parts[j] != NULL) {
        aoc_str_array_append(signal_parts, parts[j]);
        j++;
    }

    aoc_str_array_sort(signal_parts, signal_sort);

    for(j = 0; j < aoc_array_length(signal_parts); j++) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        char *part = aoc_str_array_index(signal_parts, j);
        for(size_t k = 0; k < strlen(part); k++) {
            letter_key = part[k];
            g_hash_table_add(set, (void *)(uint64_t)(letter_key));
        }
        aoc_ptr_array_append(signal_sets, set);
    }

    aoc_str_freev(parts);
    for (size_t index = 0; index < aoc_array_length(signal_parts); index++) {
        free(aoc_str_array_index(signal_parts, index));
    }
    aoc_array_free(signal_parts, 0);
    for (size_t i = 0; i < aoc_array_length(signal_sets); i++) {
        set = (GHashTable *)aoc_ptr_array_index(signal_sets, i);
        if (g_hash_table_size(set) == 5) {
            if (g_hash_table_set_intersection(set, (GHashTable *)aoc_ptr_array_index(signal_sets, signal_set_key[1])) == 2) {
                signal_set_key[3] = i;
            } else if (g_hash_table_set_intersection(set, (GHashTable *)aoc_ptr_array_index(signal_sets, signal_set_key[4])) == 2) {
                signal_set_key[2] = i;
            } else {
                signal_set_key[5] = i;
            }
        } else if (g_hash_table_size(set) == 6) {
            if (g_hash_table_set_difference(set, (GHashTable *)aoc_ptr_array_index(signal_sets, signal_set_key[4])) == 2) {
                signal_set_key[9] = i;
            } else if (g_hash_table_set_difference(set, (GHashTable *)aoc_ptr_array_index(signal_sets, signal_set_key[5])) == 2) {
                signal_set_key[0] = i;
            } else {
                signal_set_key[6] = i;
            }
        }
    }

    GHashTable **decoded;
    decoded = (GHashTable **)calloc(10, sizeof(GHashTable *));
    for (size_t hkey = 0; hkey < 10; hkey++) {
        decoded[hkey] = (GHashTable *)aoc_ptr_array_index(signal_sets, signal_set_key[hkey]);
    }

    free(signal_set_key);
    return decoded;
}

AocArrayPtr decode(GHashTable **keys, char *signal) {
    AocArrayPtr message;
    char **parts;
    AocArrayPtr signal_sets;
    GHashTable *signal_set;
    GHashTable *set;
    char letter_key;

    parts = aoc_str_split(str_trim(signal), " ", -2);
    signal_sets = aoc_ptr_array_new();
    message = aoc_int32_array_new();

    size_t j = 0;
    while (parts[j] != NULL) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        for(size_t k = 0; k < strlen(parts[j]); k++) {
            letter_key = parts[j][k];
            g_hash_table_add(set, (void *)(uint64_t)(letter_key));
        }
        aoc_ptr_array_append(signal_sets, set);
        j++;
    }
    for (size_t i = 0; i < aoc_array_length(signal_sets); i++) {
        // This is the decoding loop, where the signal is compared to the keys in the
        // decoded list of hash_tables. Again not really sure this is the best way to do this.
        signal_set = (GHashTable *)aoc_ptr_array_index(signal_sets, i);
        for (size_t j = 0; j < 10; j++) {
            set = keys[j];
            if(g_hash_table_set_compare(set, signal_set)) {
                aoc_int32_array_append(message, j);
            }
        }
        free(signal_set);
    }

    aoc_str_freev(parts);
    aoc_ptr_array_free(signal_sets);

    return message;
}

void *solve_part_1(AocData_t *data) {
    char ** split_line;
    char **output_value = NULL;
    char *val;
    int count = 0;

    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_ptr_array_index(aoc_data_get(data), i);
        output_value = aoc_str_split(str_trim(split_line[1]), " ", -1);

        int j = 0;
        while ((val = output_value[j]) != NULL) {
            if ((strlen(val) >= 2 && strlen(val) <=4) || strlen(val) == 7) {
                count++;
            }
            j++;
        }

    }
    aoc_str_freev(output_value);
    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    char **split_line;
    AocArrayPtr output;
    int array_sum;
    GHashTable **decoded;
    AocArrayPtr message = NULL;
    int message_sum;

    output = aoc_array_sized_new(AOC_ARRAY_INT32, 100);
    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_ptr_array_index(aoc_data_get(data), i);
        decoded = decode_signal(str_trim(split_line[0]));
        message = decode(decoded, str_trim(split_line[1]));
        message_sum = 0;
        for (size_t j = 0; j < aoc_array_length(message); j++) {
            message_sum += (int)pow((double)10, (double)(3 - j)) * aoc_int32_array_index(message, j);
        }

        aoc_int32_array_append(output, message_sum);
        for (size_t index = 0; index < 10; index++) {
            GHashTable *table = decoded[index];
            g_hash_table_destroy(table);
        }
        free(decoded);
    }

    array_sum = 0;
    for (size_t i = 0; i < aoc_array_length(output); i++) {
        array_sum += aoc_int32_array_index(output, i);
    }

    aoc_array_free(message, 0);

    aoc_int32_array_free(output);
    return strdup_printf("%d", array_sum);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    } return NULL;
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

#ifndef NDEBUG
    aoc_mem_wrap_up();
#endif

    return 0;
}
