#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glib.h"
#include "aoc_utils.h"

GArray *clean_input(GArray *data) { return data; }

gint solution_str(AocData_t *data, const gchar *cmp_string) {
    gint number = 0;
    GChecksum *checksum = g_checksum_new(G_CHECKSUM_MD5);
    gchar *string = NULL;
    const gchar *hashcode;
    gchar *base = g_array_index(data->data, char *, 0);

    while (TRUE) {
        string = g_strdup_printf("%s%d", base, ++number);
        g_checksum_update(checksum, (guchar *)string, -1);
        hashcode = g_checksum_get_string(checksum);
        g_free(string);
        if (strncmp(hashcode, cmp_string, strlen(cmp_string)) == 0) {
            break;
        }
        g_checksum_reset(checksum);
    }
    g_checksum_free(checksum);
    return number;
}

gint solution_bin(AocData_t *data, const gchar *cmp_string) {
    gchar string[100];
    gint number = 0;
    GChecksum *checksum = g_checksum_new(G_CHECKSUM_MD5);
    guint8 hashcode[100];
    gsize length;
    gboolean found = FALSE;

    gchar *base = g_array_index(data->data, char *, 0);

    while (!found) {
        sprintf(string, "%s%d", base, ++number);
        g_checksum_update(checksum, (guchar *)string, -1);
        length = 100;
        g_checksum_get_digest(checksum, hashcode, &length);
        if (strlen(cmp_string) == 5) {
            if ((*(hashcode + 0) == 0) && *(hashcode + 1) == 0 &&
                *(hashcode + 2) < 16) {
                found = TRUE;
            }
        } else {
            if ((*(hashcode + 0) == 0) && *(hashcode + 1) == 0 &&
                *(hashcode + 2) == 0) {
                found = TRUE;
            }
        }
        g_checksum_reset(checksum);
    }
    g_checksum_free(checksum);
    return number;
}

gpointer solve_part_1_str(AocData_t *data) {
    return g_strdup_printf("%d", solution_str(data, "00000"));
}

gpointer solve_part_2_str(AocData_t *data) {
    return g_strdup_printf("%d", solution_str(data, "000000"));
}

gpointer solve_part_1_bin(AocData_t *data) {
    return g_strdup_printf("%d", solution_bin(data, "00000"));
}

gpointer solve_part_2_bin(AocData_t *data) {
    return g_strdup_printf("%d", solution_bin(data, "000000"));
}

gpointer solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1_str, data, 1);
        timer_func(2, solve_part_2_str, data, 1);
        timer_func(1, solve_part_1_bin, data, 1);
        timer_func(2, solve_part_2_bin, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    data = aoc_data_new(filename, 2015, 4);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
