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

char *solve_part_2(GArray *data) {
    return NULL;
}


int main(int argc, char **argv) {
    GArray *data;
    gchar *filename;

    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = g_strdup("input.txt");
    }

    data = get_input(filename, 2016, 7);

    if (data) {
        TIMER_INT(1, solve_part_1(data));
        TIMER_STR(2, solve_part_2(data));

        g_array_free(data, TRUE);
    }

}
