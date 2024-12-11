#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_regex.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
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

int check_abba(regex_t *abba, const char *string) {
    regmatch_t abbaMatch[NMATCH];

    int error = regexec(abba, string, NMATCH, abbaMatch, 0);
    return (!error);
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

    char abba_pattern[] = "(.)((?!\\1).)\\2\\1";
    char hyper_pattern[] = "(\\[\\w+\\])";

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
    char *string;
    int   count;
    int   error;

    char *aba_str, *hypernet_str, *supernet_str;
    char  bab_str[4];

    AocArrayPtr data = aoc_data_get(aoc_data);

    regex_t    aba, hypernet;
    regmatch_t aba_match[10], hypernet_match[10];
    const char aba_pattern[] = "(?=((\\w)((?!\\2)\\w)\\2))";
    const char hypernet_pattern[] = "(\\[\\w+\\])";

    error = regcomp(&aba, aba_pattern, 0);
    error = regcomp(&hypernet, hypernet_pattern, 0);

    count = 0;
    const int c_nmatch = 10;

    for (unsigned int i = 0; i < aoc_array_length(data); i++) {
        string = aoc_str_array_index(data, i);
        error = regexec(&hypernet, string, c_nmatch, hypernet_match, 0);
        regex_error(error, &hypernet);
        hypernet_str = strdup("");
        unsigned offset = 0;
        while (!error) {
            char **string_list = calloc(3, sizeof(char *));
            string_list[0] = hypernet_str;
            char *substring = get_match_string(hypernet_match, string + offset);
            string_list[1] = substring;
            hypernet_str = str_join("", string_list, 2);
            free(substring);
            offset += hypernet_match[0].rm_eo;
            error = regexec(&hypernet, string + offset, c_nmatch, hypernet_match, 0);
        }

        char **re_split = regex_split("\\[\\w+\\]", string, 0);
        supernet_str = str_join("|", re_split, 10);

        error = regexec(&aba, supernet_str, c_nmatch, aba_match, 0);
        offset = 0;
        while (!error) {
            aba_str = get_match_string(aba_match, supernet_str + offset);
            snprintf(bab_str, 4, "%c%c%c", aba_str[1], aba_str[0], aba_str[1]);
            if (strstr(hypernet_str, bab_str)) {
                count++;
                break;
            }
            free(aba_str);
            // Do not offset to end of substring, in case of overlapping matches.
            offset += 1;
            error = regexec(&aba, supernet_str + offset, c_nmatch, aba_match, 0);
        }
        aoc_str_freev(re_split);
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
