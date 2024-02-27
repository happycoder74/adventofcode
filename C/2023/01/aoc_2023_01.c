#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_io.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_digit(char *string, int order) {
    if (order >= 0) { // Look from the front
        for (uint32_t i = 0; i < strlen(string); i++) {
            if (isdigit(string[i])) {
                return string[i] - '0';
            }
        }
    } else {
        for (int32_t i = (int)strlen(string) - 1; i >= 0; i--) {
            if (isdigit(string[i])) {
                return string[i] - '0';
            }
        }
    }
    return -1;
}

void *solve_part_1(AocData_t *data) {
    uint32_t    sum = 0;
    AocArrayPtr strings = aoc_data_get(data);
    for (uint32_t i = 0; i < strings->length; i++) {
        char    *string = aoc_str_array_index(strings, i);
        uint32_t first = find_digit(string, 1);
        uint32_t second = find_digit(string, -1);
        sum += first * 10 + second;
    }

    return strdup_printf("%d", sum);
}

static const char *rev_find_string(const char *haystack, const char *needle) {
    const char *haystack_end = haystack + strlen(haystack) - strlen(needle);
    const char *p = haystack_end;
    const char *found = NULL;

    while (p >= haystack) {
        found = strstr(p, needle);
        if (found) {
            return found;
        }
        p--;
    }

    return NULL;
}
char *needles[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int32_t values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void *solve_part_2(AocData_t *data) {
    uint32_t    sum = 0;
    AocArrayPtr strings = aoc_data_get(data);
    for (int32_t i = 0; i < (int)strings->length; i++) {
        char   *string = aoc_str_array_index(strings, i);
        int32_t first_index = 100;
        int32_t second_index = -100;
        int32_t first = 0;
        int32_t second = 0;

        for (int32_t i_needle = 0; i_needle < 18; i_needle++) {
            const char *found;
            char       *needle = needles[i_needle];
            if ((found = strstr(string, needle))) {
                int64_t needle_index = found - string;
                if (needle_index < first_index) {
                    first_index = (int32_t)needle_index;
                    first = values[i_needle];
                }
            }
            if ((found = rev_find_string(string, needle))) {
                int64_t needle_index = found - string;

                if (needle_index > second_index) {
                    second_index = (int32_t)needle_index;
                    second = values[i_needle];
                }
            }
        }

        sum += first * 10 + second;
    }

    return strdup_printf("%d", sum);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2023;
    const unsigned day = 1;

    AocData_t *data = get_data(argc, argv, year, day, NULL);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
