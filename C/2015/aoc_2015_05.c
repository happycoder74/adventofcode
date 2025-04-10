#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static short int check_wovel(const char *line) {
    int        result    = 0;
    const char wovels[6] = "aeiou";

    for (size_t i_wovel = 0; i_wovel < 5; ++i_wovel) {
        for (size_t i_line = 0; i_line < strlen(line); ++i_line) {
            if (line[i_line] == wovels[i_wovel])
                ++result;
        }
    }

    return result >= 3;
}

static short int check_double_letter(const char *line) {
    const size_t line_length = strlen(line);

    for (size_t i_line = 0; i_line < line_length - 1; ++i_line) {
        const char a = line[i_line];
        const char b = line[i_line + 1];
        if (a == b) {
            return 1;
        }
    }

    return 0;
}

static short int check_no_invalid(const char *line) {
    char invalid[4][3] = {"ab", "cd", "pq", "xy"};

    for (size_t i_invalid = 0; i_invalid != 4; ++i_invalid) {
        char *invalid_substring = invalid[i_invalid];
        if (strstr(line, invalid_substring) != NULL) {
            return 0;
        }
    }
    return 1;
}

static short int check_pairs(const char *line) {
    const size_t line_length = strlen(line);
    for (size_t i_line = 0; i_line < line_length - 3; ++i_line) {
        char pair[3]             = {0};
        pair[0]                  = line[i_line];
        pair[1]                  = line[i_line + 1];
        const char *rest_of_line = line + i_line + 2;
        char       *pos          = strstr(rest_of_line, pair);
        if (pos != NULL) {
            if ((size_t)(pos - line + 2) > i_line + 1) {
                return 1;
            }
        }
    }
    return 0;
}

static short int check_repeat(const char *line) {
    const size_t line_length = strlen(line);
    for (size_t i_line = 0; i_line < line_length - 2; ++i_line) {
        const char a = line[i_line];
        const char b = line[i_line + 2];
        if (a == b) {
            return 1;
        }
    }
    return 0;
}

void *solve_part_1(AocData_t *data) {
    int    count = 0;
    size_t i;
    char  *line;

    for (i = 0; i < aoc_data_length(data); i++) {
        line = aoc_str_array_index(data->data, i);

        if (check_wovel(line) && check_double_letter(line) && check_no_invalid(line)) {
            count++;
        }
    }

    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    uint32_t count = 0;
    size_t   i;
    char    *line;

    for (i = 0; i < aoc_data_length(data); i++) {
        line = aoc_str_array_index(data->data, i);

        if (check_pairs(line) && check_repeat(line)) {
            count++;
        }
    }

    return strdup_printf("%d", count);
}

void solve_all(void *input) {
    AocData_t *data = (AocData_t *)input;

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
}

int main(int argc, char **argv) {

    const unsigned year = 2015;
    const unsigned day  = 5;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_void(solve_all, data, "Time elapsed:");

    aoc_data_free(data);

    return aoc_mem_gc();
}
