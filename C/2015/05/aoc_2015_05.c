#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_timer.h"

#ifndef G_REGEX_MATCH_DEFAULT
#define G_REGEX_MATCH_DEFAULT 0
#endif

uint32_t count_matches(GRegex *pattern, char *string) {
    GMatchInfo *match_info;
    uint32_t count = 0;

    g_regex_match(pattern, string, G_REGEX_MATCH_DEFAULT, &match_info);
    while (g_match_info_matches(match_info)) {
        count++;
        g_match_info_next(match_info, NULL);
    }
    g_match_info_free(match_info);

    return count;
}

void *solve_part_1(AocData_t *data) {
    GRegex *regex_wovel, *regex_double_letter, *regex_invalid;
    int count = 0;
    size_t i;
    char *line;

    regex_wovel = g_regex_new("[aeiou]", 0, 0, NULL);
    regex_double_letter = g_regex_new("(.)\\1", 0, 0, NULL);
    regex_invalid = g_regex_new("(ab|cd|pq|xy)", 0, 0, NULL);

    for (i = 0; i < data->data->len; i++) {
        line = g_array_index(data->data, char *, i);
        if ((count_matches(regex_wovel, line) >= 3) &&
            (count_matches(regex_double_letter, line) > 0) &&
            (count_matches(regex_invalid, line) == 0)) {
            count++;
        }
    }

    g_regex_unref(regex_wovel);
    g_regex_unref(regex_double_letter);
    g_regex_unref(regex_invalid);

    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    GRegex *regex_pairs, *regex_repeat;
    uint32_t count = 0;
    size_t i;
    gchar *line;

    regex_pairs = g_regex_new("([a-z][a-z])\\w*\\1", 0, 0, NULL);
    regex_repeat = g_regex_new("(.)\\w\\1", 0, 0, NULL);

    for (i = 0; i < data->data->len; i++) {
        line = g_array_index(data->data, char *, i);
        if ((count_matches(regex_pairs, line) > 0) &&
            (count_matches(regex_repeat, line) > 0)) {
            count++;
        }
    }

    g_regex_unref(regex_pairs);
    g_regex_unref(regex_repeat);

    return strdup_printf("%d", count);
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

    char sourcefile[100];
    int year, day;

    strcpy(sourcefile, basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, NULL);
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}

