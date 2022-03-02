#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"
#include <math.h>

GArray *clean_input(GArray *data) {
    GArray *result;
    guint i;
    gchar **split_line;

    result = g_array_new(TRUE, FALSE, sizeof(gchar **));
    for (i = 0; i < data->len; i++) {
        split_line = g_strsplit(g_array_index(data, gchar *, i), "|", -1);
        g_array_append_val(result, split_line);
    }

    return result;
}

static gboolean g_hash_table_set_compare(GHashTable *a, GHashTable *b) {
    GHashTableIter iter;
    gpointer key, value;

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
    guint diff_size;
    GHashTableIter iter;
    gpointer key, value;

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
    gpointer key, value;

    g_hash_table_iter_init(&iter, a);
    while(g_hash_table_iter_next(&iter, &key, &value)) {
        if(g_hash_table_contains(b, key))
            common_keys += 1;
    }
    return common_keys;
}

gint signal_sort(gconstpointer a, gconstpointer b) {
    const char *str1 = *((char **) a);
    const char *str2 = *((char **) b);

    return strlen(str1) - strlen(str2);
}

GHashTable **decode_signal(char *signal) {
    int *signal_set_key;
    GArray *signal_sets;
    gchar **parts;
    GHashTable *set;
    GPtrArray *signal_parts;
    gchar letter_key;

    signal_set_key = g_new0(int, 10);
    signal_set_key[1] = 0;
    signal_set_key[7] = 1;
    signal_set_key[4] = 2;
    signal_set_key[8] = 9;

    signal_sets = g_array_new(FALSE, FALSE, sizeof(GHashTable *));
    signal_parts = g_ptr_array_new();
    parts = g_strsplit(g_strstrip(signal), " ", -1);
    guint j = 0;
    while (parts[j] != NULL) {
        g_ptr_array_add(signal_parts, parts[j]);
        j++;
    }

    // Sorting function does not seem to work. Does it not work with strings??
    g_ptr_array_sort(signal_parts, signal_sort);

    for(j = 0; j < signal_parts->len; j++) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        gchar *part = g_ptr_array_index(signal_parts, j);
        for(guint k = 0; k < strlen(part); k++) {
            letter_key = part[k];
            g_hash_table_add(set, GUINT_TO_POINTER(letter_key));
        }
        g_array_append_val(signal_sets, set);
    }
    for (guint i = 0; i < signal_sets->len; i++) {
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
    decoded = g_new(GHashTable *, 10);
    for (guint hkey = 0; hkey < 10; hkey++) {
        decoded[hkey] = g_array_index(signal_sets, GHashTable *, signal_set_key[hkey]);
    }
    return decoded;
}

GArray *decode(GHashTable **keys, gchar *signal) {
    GArray *message;
    gchar **parts;
    GArray *signal_sets;
    GHashTable *signal_set;
    GHashTable *set;
    gchar letter_key;

    parts = g_strsplit(g_strstrip(signal), " ", -1);
    signal_sets = g_array_new(FALSE, FALSE, sizeof(GHashTable *));
    message = g_array_new(FALSE, FALSE, sizeof(int));

    guint j = 0;
    while (parts[j] != NULL) {
        set = g_hash_table_new(g_direct_hash, g_direct_equal);
        for(guint k = 0; k < strlen(parts[j]); k++) {
            letter_key = parts[j][k];
            g_hash_table_add(set, GUINT_TO_POINTER(letter_key));
        }
        g_array_append_val(signal_sets, set);
        j++;
    }
    for (guint i = 0; i < signal_sets->len; i++) {
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
    return message;
}

int solve_part_1(GArray *data) {
    gchar **split_line;
    gchar **output_value;
    gchar *val;
    gint count = 0;
    for (guint i = 0; i < data->len; i++) {
        split_line = g_array_index(data, char **, i);
        output_value = g_strsplit(g_strstrip(split_line[1]), " ", -1);

        gint j = 0;
        while ((val = output_value[j]) != NULL) {
            if ((strlen(val) >= 2 && strlen(val) <=4) || strlen(val) == 7) {
                count++;
            }
            j++;
        }

    }
    return count;
}

int solve_part_2(GArray *data) {
    gchar **split_line;
    GArray *output;
    int array_sum;
    GHashTable **decoded;
    GArray *message;
    int message_sum;

    output = g_array_new(FALSE, FALSE, sizeof(int));
    for (guint i = 0; i < data->len; i++) {
        split_line = g_array_index(data, char **, i);
        decoded = decode_signal(g_strstrip(split_line[0]));
        message = decode(decoded, g_strstrip(split_line[1]));
        message_sum = 0;
        for (guint j = 0; j < message->len; j++) {
            message_sum += (int)pow((double)10, (double)(3 - j)) * g_array_index(message, int, j);
        }

        g_array_append_val(output, message_sum);
    }

    array_sum = 0;
    for (guint i = 0; i < output->len; i++) {
        array_sum += g_array_index(output, int, i);
    }

    return array_sum;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = clean_input(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), INT, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2021, 8), INT, 0);
    g_free(filename);
}
