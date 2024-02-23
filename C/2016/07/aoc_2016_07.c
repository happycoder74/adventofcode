#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_regex.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <glib.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMATCH 20

int check_match(regmatch_t *match_info, const char *string) {
    for (unsigned i = 0; i < 3; i++) {
        if (match_info[0].rm_so < 0) {
            return 0;
        }
    }
    return !(string[match_info[1].rm_so] == string[match_info[2].rm_so]);
}

void print_match(regmatch_t *match_info, const char *string) {
    printf("%s\n", string);
    int index = 0;
    while (match_info[index].rm_so >= 0) {
        regmatch_t mo = match_info[index];
        printf(" (%d, %d)\n", mo.rm_so, mo.rm_eo);
        index++;
    }
}

int check_abba(regex_t *abba, const char *string) {
    regmatch_t abbaMatch[NMATCH];

    int error = regexec(abba, string, NMATCH, abbaMatch, 0);
    return (!error) && check_match(abbaMatch, string);
}

int check_hypernet(regex_t *regex, regex_t *hypernet, char *str) {
    regmatch_t hypernetMatch[NMATCH];
    unsigned   offset = 0;

    int error = regexec(hypernet, str + offset, NMATCH, hypernetMatch, 0);
    while (!error) {
        char *hn_string = get_match_string(hypernetMatch, str + offset);
        if (check_abba(regex, hn_string)) {
            free(hn_string);
            return 0;
        }
        free(hn_string);
        offset += hypernetMatch[1].rm_eo;
        if (offset >= strlen(str)) {
            break;
        }
        error = regexec(hypernet, str + offset, NMATCH, hypernetMatch, 0);
    }
    return error;
}

void *solve_part_1(AocData_t *aoc_data) {
    int      error = 0;
    unsigned count = 0;
    regex_t  abba, hypernet;

    AocArrayPtr data = aoc_data_get(aoc_data);

    char abba_pattern[] = "([a-z])([a-z])\\2\\1";
    char hyper_pattern[] = "(\\[\\w+\\])";
    // error = regcomp(&abba, "(.)((?!\\1).)\\2\\1", REG_EXTENDED);
    error = regcomp(&abba, abba_pattern, REG_EXTENDED);
    regex_error(error, &abba);

    error = regcomp(&hypernet, hyper_pattern, REG_EXTENDED);
    regex_error(error, &hypernet);

    for (unsigned i = 0; i < data->length; i++) {
        char *str = aoc_str_array_index(data, i);
        if (check_hypernet(&abba, &hypernet, str)) {
            if (check_abba(&abba, str)) {
                count++;
            }
        }
    }

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

// int main(int argc, char *argv[]) {
//
//     test_check_abba("[bddb]", true);
//     test_check_hyper("abcd[bddb]xyyx", false);
//
//     return EXIT_SUCCESS;
// }

int main(int argc, char **argv) {

    const unsigned year = 2016;
    const unsigned day = 7;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);
}
