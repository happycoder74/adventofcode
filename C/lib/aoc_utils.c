#include <glib.h>
#include <aoc_utils.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int str_count(char *str, char needle, int start, int end) {
    int i;
    int count = 0;
    if (end < 0) {
        end = (int)strlen(str) - 1 - end;
    }
    if (start < 0) {
        start = (int)strlen(str) - 1 - start;
    }

    for (i = start; i < end; i++) {
        if (needle == str[i]) {
            count ++;
        }
    }
    return count;
}

char *substr(char *str, int start, int end) {
    char *substr;
    int i;
    if (end < 0) {
        end = (int)strlen(str) - 1 + end + 1;
    }
    if (start < 0) {
        start = (int)strlen(str) - 1 + start + 1;
    }

    assert(end <= (int)strlen(str));
    assert(start >= 0);
    assert(end >= 0);
    assert(start < (int)strlen(str));
    assert(start <= end);

    substr = malloc(sizeof(char) * (end - start + 1));
    for (i = 0; i < (end - start); i++) {
        substr[i] = str[start + i];
    }
    substr[i] = '\0';
    return substr;
}

int str_startswith(char *str, char *start_str) {
    char *sstr;
    int result;

    sstr = substr(str, 0, strlen(start_str));
    result = !strcmp(start_str, sstr);
    free(sstr);
    return result;
}

int str_endswith(char *str, char *end_str) {
    char *sstr;
    int result;

    sstr = substr(str, -strlen(end_str), strlen(str));
    result = !strcmp(end_str, sstr);
    free(sstr);
    return result;
}


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

