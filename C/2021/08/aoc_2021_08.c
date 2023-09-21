#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"
#include <math.h>

GArray *clean_data(GArray *data) {
    GArray *result;
    size_t i;
    char **split_line;

    result = g_array_new(TRUE, FALSE, sizeof(char **));
    for (i = 0; i < data->len; i++) {
        split_line = g_strsplit(g_array_index(data, char *, i), "|", -1);
        g_array_append_val(result, split_line);
    }

    return result;
}

static gboolean g_hash_table_set_compare(GHashTable *a, GHashTable *b) {
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

static gint g_hash_table_set_difference(GHashTable *a, GHashTable *b) {
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

static gint g_hash_table_set_intersection(GHashTable *a, GHashTable *b) {
    guint common_keys = 0;
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
    GArray *signal_sets;
    char **parts;
    GHashTable *set;
    GPtrArray *signal_parts;
    char letter_key;

    signal_set_key = (int *)calloc(10, sizeof(int));
    signal_set_key[1] = 0;
    signal_set_key[7] = 1;
    signal_set_key[4] = 2;
    signal_set_key[8] = 9;

    signal_sets = g_array_new(FALSE, FALSE, sizeof(GHashTable *));
    signal_parts = g_ptr_array_new();
    parts = g_strsplit(g_strstrip(signal), " ", -1);
    unsigned int j = 0;
    while (parts[j] != NULL) {
        g_ptr_array_add(signal_parts, parts[j]);
        j++;
    }

    // Sorting function does not seem to work. Does it not work with strings??
    g_ptr_array_sort(signal_parts, signal_sort);

    for(j = 0; j < signal_parts->len; j++) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        char *part = g_ptr_array_index(signal_parts, j);
        for(guint k = 0; k < strlen(part); k++) {
            letter_key = part[k];
            g_hash_table_add(set, GUINT_TO_POINTER(letter_key));
        }
        g_array_append_val(signal_sets, set);
    }
    for (unsigned int i = 0; i < signal_sets->len; i++) {
        set = g_array_index(signal_sets, GHashTable *, i);
        if (g_hash_table_size(set) == 5) {
            if (g_hash_table_set_intersection(set, g_array_index(signal_sets, GHashTable *, signal_set_key[1])) == 2) {
                signal_set_key[3] = i;
            } else if (g_hash_table_set_intersection(set, g_array_index(signal_sets, GHashTable *, signal_set_key[4])) == 2) {
                signal_set_key[2] = i;
            } else {
                signal_set_key[5] = i;
            }
        } else if (g_hash_table_size(set) == 6) {
            if (g_hash_table_set_difference(set, g_array_index(signal_sets, GHashTable *, signal_set_key[4])) == 2) {
                signal_set_key[9] = i;
            } else if (g_hash_table_set_difference(set, g_array_index(signal_sets, GHashTable *, signal_set_key[5])) == 2) {
                signal_set_key[0] = i;
            } else {
                signal_set_key[6] = i;
            }
        }
    }

    GHashTable **decoded;
    decoded = (GHashTable **)calloc(10, sizeof(GHashTable *));
    for (unsigned int hkey = 0; hkey < 10; hkey++) {
        decoded[hkey] = g_array_index(signal_sets, GHashTable *, signal_set_key[hkey]);
    }

    return decoded;
}

GArray *decode(GHashTable **keys, gchar *signal) {
    GArray *message;
    char **parts;
    GArray *signal_sets;
    GHashTable *signal_set;
    GHashTable *set;
    char letter_key;

    parts = g_strsplit(g_strstrip(signal), " ", -2);
    signal_sets = g_array_new(FALSE, FALSE, sizeof(GHashTable *));
    message = g_array_new(FALSE, FALSE, sizeof(int));

    unsigned int j = 0;
    while (parts[j] != NULL) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        for(guint k = 0; k < strlen(parts[j]); k++) {
            letter_key = parts[j][k];
            g_hash_table_add(set, GUINT_TO_POINTER(letter_key));
        }
        g_array_append_val(signal_sets, set);
        j++;
    }
    for (unsigned int i = 0; i < signal_sets->len; i++) {
    // This is the decoding loop, where the signal is compared to the keys in the
    // decoded list of hash_tables. Again not really sure this is the best way to do this.
        signal_set = g_array_index(signal_sets, GHashTable *, i);
        for (guint j = 0; j < 10; j++) {
            set = keys[j];
            if(g_hash_table_set_compare(set, signal_set)) {
                g_array_append_val(message, j);
            }
        }
    }
    g_strfreev(parts);
    return message;
}

void *solve_part_1(AocData_t *data) {
    char **split_line;
    char **output_value;
    char *val;
    int count = 0;
    for (size_t i = 0; i < data->data->len; i++) {
        split_line = g_array_index(data->data, char **, i);
        output_value = g_strsplit(g_strstrip(split_line[1]), " ", -1);

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
    GArray *output;
    int array_sum;
    GHashTable **decoded;
    GArray *message;
    int message_sum;

    output = g_array_new(FALSE, FALSE, sizeof(int));
    for (size_t i = 0; i < data->data->len; i++) {
        split_line = g_array_index(data->data, char **, i);
        decoded = decode_signal(g_strstrip(split_line[0]));
        message = decode(decoded, g_strstrip(split_line[1]));
        message_sum = 0;
        for (size_t j = 0; j < message->len; j++) {
            message_sum += (int)pow((double)10, (double)(3 - j)) * g_array_index(message, int, j);
        }

        g_array_append_val(output, message_sum);
    }

    array_sum = 0;
    for (size_t i = 0; i < output->len; i++) {
        array_sum += g_array_index(output, int, i);
    }

    return strdup_printf("%d", array_sum);
}

void *solve_all(AocData_t *data) {

    data->data = clean_data(get_input(data->filename, data->year, data->day));

    if (data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    char *sourcefile;
    int year, day;

    sourcefile = basename(__FILE__);
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);

    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
