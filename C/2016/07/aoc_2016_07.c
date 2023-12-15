#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *solve_part_1(AocData_t *aoc_data) {
    GError      *regex_error = NULL;
    GMatchInfo  *matchInfo, *hypernetInfo, *abba_hn_info;
    char        *str;
    unsigned int i;
    int          count = 0;
    char        *matchStr, *hypernetStr;
    short        ok;

    AocArrayPtr data = aoc_data_get(aoc_data);

    GRegex *abba = g_regex_new("(.)((?!\\1).)\\2\\1", 0, 0, &regex_error);
    if (regex_error) {
        fprintf(stderr, "Error in pattern\n%s\n", regex_error->message);
        exit(EXIT_FAILURE);
    }
    GRegex *hypernet = g_regex_new("(\\[\\w+\\])", 0, 0, &regex_error);
    if (regex_error) {
        fprintf(stderr, "Error in pattern\n%s\n", regex_error->message);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < aoc_array_length(data); i++) {
        str = aoc_str_array_index(data, i);
        g_regex_match(abba, str, 0, &matchInfo);
        g_regex_match(hypernet, str, 0, &hypernetInfo);
        ok = g_match_info_matches(matchInfo);
        while (g_match_info_matches(matchInfo) && ok) {
            matchStr = g_match_info_fetch(matchInfo, 0);
            if (matchStr != NULL) {
                while (g_match_info_matches(hypernetInfo) && ok) {
                    hypernetStr = g_match_info_fetch(hypernetInfo, 0);
                    if (hypernetStr != NULL) {
                        g_regex_match(abba, hypernetStr, 0, &abba_hn_info);
                        if (g_match_info_get_match_count(abba_hn_info) != 0) {
                            ok = FALSE;
                        }
                    }
                    g_match_info_next(hypernetInfo, &regex_error);
                    if (hypernetStr)
                        free(hypernetStr);
                }
            }
            if (matchStr)
                free(matchStr);

            g_match_info_next(matchInfo, &regex_error);
            if (!ok)
                break;
        }
        if (ok)
            count++;
    }

    g_regex_unref(abba);
    g_regex_unref(hypernet);

    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *aoc_data) {
    char       *string;
    int         count;
    GError     *err = NULL;
    GMatchInfo *abaInfo, *hypernetInfo;
    char       *aba_str, *hypernet_str, *supernet_str;
    char        bab_str[4];

    AocArrayPtr data = aoc_data_get(aoc_data);

    GRegex *aba = g_regex_new("(?=((\\w)((?!\\2)\\w)\\2))", 0, 0, &err);
    GRegex *hypernet = g_regex_new("(\\[\\w+\\])", 0, 0, &err);
    count = 0;

    for (unsigned int i = 0; i < aoc_array_length(data); i++) {
        string = aoc_str_array_index(data, i);
        g_regex_match(hypernet, string, 0, &hypernetInfo);

        hypernet_str = strdup("");
        while (g_match_info_matches(hypernetInfo)) {
            hypernet_str = g_strjoin("", hypernet_str, g_match_info_fetch(hypernetInfo, 1), NULL);
            g_match_info_next(hypernetInfo, &err);
        }
        supernet_str = g_strjoinv("|", g_regex_split(g_regex_new("\\[\\w+\\]", 0, 0, &err), string, 0));

        g_regex_match(aba, supernet_str, 0, &abaInfo);
        while (g_match_info_matches(abaInfo)) {
            aba_str = g_match_info_fetch(abaInfo, 1);
            sprintf(bab_str, "%c%c%c", aba_str[1], aba_str[0], aba_str[1]);
            if (strstr(hypernet_str, bab_str)) {
                count++;
                break;
            }
            g_match_info_next(abaInfo, &err);
        }
        free(supernet_str);
        free(hypernet_str);
    }
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

    char sourcefile[20];
    int  year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new("test_input.txt", year, day);
        } else {
            data = aoc_data_new(argv[1], year, day);
        }
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
