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

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr result;
    size_t i;
    char **split_line;

    result = aoc_array_new(sizeof(char **));
    for (i = 0; i < aoc_array_length(data); i++) {
        split_line = aoc_str_split(aoc_str_array_index(data, i), "|", -1);
        aoc_array_append(result, split_line);
    }

    // Note we do not free split line here, since the memory is used in the new array.

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

    signal_sets = aoc_array_new(sizeof(GHashTable *));
    signal_parts = aoc_array_new(sizeof(char *));
    parts = aoc_str_split(g_strstrip(signal), " ", -1);
    size_t j = 0;
    while (parts[j] != NULL) {
        aoc_str_array_append(signal_parts, parts[j]);
        j++;
    }

    aoc_str_array_sort(signal_parts, signal_sort);

    for(j = 0; j < aoc_array_length(signal_parts); j++) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        char *part = (char *)aoc_array_index(signal_parts, j);
        for(size_t k = 0; k < strlen(part); k++) {
            letter_key = part[k];
            g_hash_table_add(set, (void *)(uint64_t)(letter_key));
        }
        aoc_array_append(signal_sets, set);
    }
    for (size_t i = 0; i < aoc_array_length(signal_sets); i++) {
        set = (GHashTable *)aoc_array_index(signal_sets, i);
        if (g_hash_table_size(set) == 5) {
            if (g_hash_table_set_intersection(set, (GHashTable *)aoc_array_index(signal_sets, signal_set_key[1])) == 2) {
                signal_set_key[3] = i;
            } else if (g_hash_table_set_intersection(set, (GHashTable *)aoc_array_index(signal_sets, signal_set_key[4])) == 2) {
                signal_set_key[2] = i;
            } else {
                signal_set_key[5] = i;
            }
        } else if (g_hash_table_size(set) == 6) {
            if (g_hash_table_set_difference(set, (GHashTable *)aoc_array_index(signal_sets, signal_set_key[4])) == 2) {
                signal_set_key[9] = i;
            } else if (g_hash_table_set_difference(set, (GHashTable *)aoc_array_index(signal_sets, signal_set_key[5])) == 2) {
                signal_set_key[0] = i;
            } else {
                signal_set_key[6] = i;
            }
        }
    }

    GHashTable **decoded;
    decoded = (GHashTable **)calloc(10, sizeof(GHashTable *));
    for (size_t hkey = 0; hkey < 10; hkey++) {
        decoded[hkey] = (GHashTable *)aoc_array_index(signal_sets, signal_set_key[hkey]);
    }

    return decoded;
}

AocArrayPtr decode(GHashTable **keys, char *signal) {
    AocArrayPtr message;
    char **parts;
    AocArrayPtr signal_sets;
    GHashTable *signal_set;
    GHashTable *set;
    char letter_key;

    parts = aoc_str_split(g_strstrip(signal), " ", -2);
    signal_sets = aoc_array_new(sizeof(GHashTable *));
    message = aoc_array_new(sizeof(int));

    size_t j = 0;
    while (parts[j] != NULL) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        for(size_t k = 0; k < strlen(parts[j]); k++) {
            letter_key = parts[j][k];
            g_hash_table_add(set, (void *)(uint64_t)(letter_key));
        }
        aoc_array_append(signal_sets, set);
        j++;
    }
    for (size_t i = 0; i < aoc_array_length(signal_sets); i++) {
    // This is the decoding loop, where the signal is compared to the keys in the
    // decoded list of hash_tables. Again not really sure this is the best way to do this.
        signal_set = (GHashTable *)aoc_array_index(signal_sets, i);
        for (size_t j = 0; j < 10; j++) {
            set = keys[j];
            if(g_hash_table_set_compare(set, signal_set)) {
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
    char *val;
    int count = 0;
    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_array_index(aoc_data_get(data), i);
        output_value = aoc_str_split(g_strstrip(split_line[1]), " ", -1);

        int j = 0;
        while ((val = output_value[j]) != NULL) {
            if ((strlen(val) >= 2 && strlen(val) <=4) || strlen(val) == 7) {
                count++;
            }
            j++;
        }

    }
    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    char **split_line;
    AocArrayPtr output;
    int array_sum;
    GHashTable **decoded;
    AocArrayPtr message;
    int message_sum;

    output = aoc_array_new(sizeof(int));
    for (size_t i = 0; i < aoc_data_length(data); i++) {
        split_line = (char **)aoc_array_index(aoc_data_get(data), i);
        decoded = decode_signal(g_strstrip(split_line[0]));
        message = decode(decoded, g_strstrip(split_line[1]));
        message_sum = 0;
        for (size_t j = 0; j < aoc_array_length(message); j++) {
            message_sum += (int)pow((double)10, (double)(3 - j)) * aoc_int_array_index(message, j);
        }

        aoc_int_array_append(output, message_sum);
    }

    array_sum = 0;
    for (size_t i = 0; i < aoc_array_length(output); i++) {
        array_sum += aoc_int_array_index(output, i);
    }

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
        data = aoc_data_new_clean(argv[1], year, day, clean_input);
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
