#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"


int solve_part_1(GArray *data) {
    GError *regex_error = NULL;
    GMatchInfo *matchInfo, *hypernetInfo, *abba_hn_info;
    gchar *str;
    guint i;
    gint count = 0;
    gchar *matchStr, *hypernetStr;
    gboolean ok;

    GRegex *abba = g_regex_new("(.)((?!\\1).)\\2\\1", 0, 0, &regex_error);
    if (regex_error) {
        g_print("Error in pattern\n%s\n", regex_error->message);
        exit(1);
    }
    GRegex *hypernet = g_regex_new("(\\[\\w+\\])", 0, 0, &regex_error);
    if (regex_error) {
        g_print("Error in pattern\n%s\n", regex_error->message);
        exit(1);
    }

    for (i = 0; i < data->len; i++) {
        str = g_array_index(data, char *, i);
        g_regex_match(abba, str, 0, &matchInfo);
        g_regex_match(hypernet, str, 0, &hypernetInfo);
        ok = g_match_info_matches (matchInfo);
        while (g_match_info_matches (matchInfo) && ok) {
            matchStr = g_match_info_fetch(matchInfo, 0);
            if (matchStr != NULL) {
                while (g_match_info_matches (hypernetInfo) && ok) {
                    hypernetStr = g_match_info_fetch(hypernetInfo, 0);
                    if (hypernetStr != NULL) {
                        g_regex_match(abba, hypernetStr, 0, &abba_hn_info);
                        if (g_match_info_get_match_count(abba_hn_info) != 0) {
                            ok = FALSE;
                        }
                    }
                    g_match_info_next(hypernetInfo, &regex_error);
                    if (hypernetStr)
                        g_free(hypernetStr);
                }
            }
            if(matchStr)
                g_free(matchStr);

            g_match_info_next (matchInfo, &regex_error);
            if (!ok)
                break;
        }
        if (ok)
            count++;
    }

    g_regex_unref(abba);
    g_regex_unref(hypernet);

    return count;
}

int solve_part_2(GArray *data) {
    char *string;
    int count;
    GError *err = NULL;
    GMatchInfo *abaInfo, *hypernetInfo;
    char *aba_str, *hypernet_str, *supernet_str;
    char bab_str[4];
    int i;


    GRegex *aba = g_regex_new("(?=((\\w)((?!\\2)\\w)\\2))", 0, 0, &err);
    GRegex *hypernet = g_regex_new("(\\[\\w+\\])", 0, 0, &err);
    count = 0;

    for (i = 0; i < (int)data->len; i++) {
        string = g_array_index(data, char *, i);
        g_regex_match(hypernet, string, 0, &hypernetInfo);

        hypernet_str = g_strdup("");
        while (g_match_info_matches(hypernetInfo)) {
            hypernet_str = g_strjoin("", hypernet_str, g_match_info_fetch(hypernetInfo, 1), NULL);
            g_match_info_next(hypernetInfo, &err);
        }
        supernet_str = g_strjoinv("|", g_regex_split(g_regex_new("\\[\\w+\\]", 0, 0, &err), string, 0));

        g_regex_match(aba, supernet_str, 0, &abaInfo);
        while (g_match_info_matches(abaInfo)){
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
    return count;
}


int solve_all(char *filename, int year, int day) {
    GArray *data;

    data = get_input(filename, year, day);

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
        filename = argv[1];
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2016, 7), INT, 0);

    return 0;
}
