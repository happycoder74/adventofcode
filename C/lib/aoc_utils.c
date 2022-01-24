#include <glib.h>
#include <aoc_utils.h>
#include <stdio.h>


GArray *get_input(char *filename, int year, int day) {
    FILE *fp;
    GArray *data;
    gchar *line = NULL;
    size_t line_length = 0;
    gchar *data_line;
    gchar *path;
    gchar *file = NULL;

    path = g_strdup_printf("../../../data/%d/%02d/", year, day);
    data = g_array_new(FALSE, FALSE, sizeof(char *));
    file = g_strconcat(path, filename, NULL);

    g_print("%s\n", file);

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file!\n");
        return NULL;
    } 

    while ((getline(&line, &line_length, fp)) != -1 ) {
        data_line = g_strstrip(g_strdup(line));
        g_array_append_val(data, data_line);
    }

    if (file) {
        g_free(file);
    }
    g_free(path);

    return data;;
}

gint max(gint *arr, gint length) {
    gint max = arr[0];
    gint i;

    for (i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

gint min(gint *arr, gint length) {
    gint min = arr[0];
    gint i;

    for (i = 1; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

gint min_non_zero(gint *arr, gint length) {
    gint min = length;
    gint i;

    for (i = 0; i < length; i++) {
        if ((arr[i] < min) && (arr[i] != 0)) {
            min = arr[i];
        }
    }
    return min;
}

