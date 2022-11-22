#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

GArray *clean_input(GArray *data) {
    return data;
}

gint count_matches(GRegex *pattern, gchar *string) {
    GMatchInfo *match_info;
    gint count = 0;

    g_regex_match(pattern, string, G_REGEX_MATCH_DEFAULT, &match_info);
    while(g_match_info_matches(match_info)) {
        count++;
        g_match_info_next(match_info, NULL);
    }
    g_match_info_free (match_info);

    return count;
}

gpointer solve_part_1(AocData_t *data) {
    GRegex *regex_wovel, *regex_double_letter, *regex_invalid;
    int count = 0;
    guint i;
    gchar *line;

    regex_wovel = g_regex_new("[aeiou]", 0, 0, NULL);
    regex_double_letter = g_regex_new("(.)\\1", 0, 0, NULL);
    regex_invalid = g_regex_new("(ab|cd|pq|xy)", 0, 0, NULL);

    for (i = 0; i < data->data->len; i++) {
        line = g_array_index(data->data, gchar *, i);
        if ((count_matches(regex_wovel, line) >= 3) &&
            (count_matches(regex_double_letter, line) > 0) &&
            (count_matches(regex_invalid, line) == 0)) {
            count++;
        }
    }

    g_regex_unref(regex_wovel);
    g_regex_unref(regex_double_letter);
    g_regex_unref(regex_invalid);

    return g_strdup_printf("%d", count);
}

gpointer solve_part_2(AocData_t *data) {
    GRegex *regex_pairs, *regex_repeat;
    int count = 0;
    guint i;
    gchar *line;

    regex_pairs = g_regex_new("([a-z][a-z])\\w*\\1", 0, 0, NULL);
    regex_repeat = g_regex_new("(.)\\w\\1", 0, 0, NULL);

    for (i = 0; i < data->data->len; i++) {
        line = g_array_index(data->data, gchar *, i);
        if ((count_matches(regex_pairs, line) > 0) &&
            (count_matches(regex_repeat, line) > 0)) {
            count++;
        }
    }

    g_regex_unref(regex_pairs);
    g_regex_unref(regex_repeat);

    return g_strdup_printf("%d", count);
}

gpointer solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));


    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
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

    data = aoc_data_new(filename, 2015, 5);
    g_free(filename);

    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
