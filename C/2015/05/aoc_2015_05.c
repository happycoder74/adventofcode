#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tre/tre.h>

uint32_t count_matches(regex_t *pattern, const char *string, int method) {
    regmatch_t match_info[20];
    int        error = 0;
    uint32_t   count = 0;
    uint32_t   offset = 0;
    char       error_string[100];

    if (method == 1) {
        while (!(error = regexec(pattern, string + offset, 20, match_info, 0))) {
            offset += match_info->rm_so + 1;
            count++;
        }
    } else {
        error = regexec(pattern, string, 20, match_info, 0);
        int counter = 1;
        if (!error) {
            while (match_info[count].rm_so >= 0) {
                count++;
            }
        }
    }

    if (error) {
        regerror(error, pattern, error_string, 100);
        if (error != 1) {
            fprintf(stderr, "Got error: %s (%d)\n", error_string, error);
        }
    }

    return count;
}

void *solve_part_1(AocData_t *data) {
    regex_t regex_wovel, regex_double_letter, regex_invalid;
    int     count = 0;
    size_t  i;
    char   *line;
    int     error;
    char    error_string[100];

    error = regcomp(&regex_wovel, "[aeiou]", REG_EXTENDED);
    if (error) {
        regerror(error, &regex_wovel, error_string, 100);
    }
    error = regcomp(&regex_double_letter, "(.)\\1", REG_EXTENDED);
    if (error) {
        regerror(error, &regex_double_letter, error_string, 100);
    }
    error = regcomp(&regex_invalid, "(ab|cd|pq|xy)", REG_EXTENDED);
    if (error) {
        regerror(error, &regex_invalid, error_string, 100);
    }

    for (i = 0; i < aoc_data_length(data); i++) {
        line = aoc_str_array_index(data->data, i);
        if ((count_matches(&regex_wovel, line, 1) >= 3) && (count_matches(&regex_double_letter, line, 2) > 0) && (count_matches(&regex_invalid, line, 2) == 0)) {
            count++;
        }
    }

    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    regex_t  regex_pairs, regex_repeat;
    uint32_t count = 0;
    size_t   i;
    char    *line;
    int      error;
    char     error_string[100];

    error = regcomp(&regex_pairs, "\\w*([a-z][a-z])\\w*\\1", REG_EXTENDED);
    if (error) {
        regerror(error, &regex_pairs, error_string, 100);
    }
    error = regcomp(&regex_repeat, "(.)\\w\\1", REG_EXTENDED);
    if (error) {
        regerror(error, &regex_repeat, error_string, 100);
    }

    for (i = 0; i < aoc_data_length(data); i++) {
        line = aoc_str_array_index(data->data, i);
        if ((count_matches(&regex_pairs, line, 2) > 0) && (count_matches(&regex_repeat, line, 2) > 0)) {
            count++;
        }
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

    const unsigned year = 2015;
    const unsigned day = 5;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
