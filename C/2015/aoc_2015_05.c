#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_regex.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *solve_part_1(AocData_t *data) {
    regex_t regex_wovel, regex_double_letter, regex_invalid;
    int     count = 0;
    size_t  i;
    char   *line;
    int     error;

    error = regcomp(&regex_wovel, "[aeiou].*[aeiou].*[aeiou]", 0);
    regex_error(error, &regex_wovel);
    error = regcomp(&regex_double_letter, "(.)\\1", 0);
    regex_error(error, &regex_double_letter);
    error = regcomp(&regex_invalid, "(ab|cd|pq|xy)", 0);
    regex_error(error, &regex_invalid);

    for (i = 0; i < aoc_data_length(data); i++) {
        int count_wovels = 0;
        int count_doubles = 0;
        int count_invalid = 0;

        line = aoc_str_array_index(data->data, i);

        error = regexec(&regex_wovel, line, 0, NULL, 0);
        if (!error) {
            count_wovels = 1;
        }

        error = regexec(&regex_double_letter, line, 0, NULL, 0);
        if (!error) {
            count_doubles = 1;
        }

        error = regexec(&regex_invalid, line, 0, NULL, 0);
        if (error == REG_NOMATCH) {
            count_invalid = 1;
        }

        if (count_wovels && count_doubles && count_invalid) {
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

    error = regcomp(&regex_pairs, "(..).*\\1", 0);
    regex_error(error, &regex_pairs);
    error = regcomp(&regex_repeat, "(.).\\1", 0);
    regex_error(error, &regex_repeat);

    for (i = 0; i < aoc_data_length(data); i++) {
        line = aoc_str_array_index(data->data, i);
        int count_pairs = 0;
        int count_repeat = 0;

        error = regexec(&regex_pairs, line, 0, NULL, 0);
        if (!error) {
            count_pairs = 1;
        }

        error = regexec(&regex_repeat, line, 0, NULL, 0);
        if (!error) {
            count_repeat = 1;
        }

        if (count_pairs && count_repeat) {
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
