#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_array.h"
#include "aoc_timer.h"

bool check_rules(int number, int part) {
    char str[7];
    char d;
    bool double_digit = FALSE;
    int n_digits = 0, min_double_digits = INT_MAX;
    int i;

    sprintf(str, "%d", number);
    d = str[0];

    if (part == 1) {
        for (int i = 1; i < 6; i++) {
            if (str[i] < d)
                return FALSE;
            if (str[i] == d)
                double_digit = TRUE;
            d = str[i];
        }
        return double_digit;
    } else {
        for (i = 1; i < 6; i++) {
            if (str[i] < d) {
                return FALSE;
            }
            if (str[i] == d) {
                n_digits++;
            } else {
                if (n_digits > 0) {
                    min_double_digits = MIN(min_double_digits, n_digits);
                    n_digits = 0;
                }
            }
            d = str[i];
        }
        if (n_digits > 0)
            min_double_digits = MIN(min_double_digits, n_digits);
        return min_double_digits == 1;
    }

}

AocArrayPtr clean_input(AocArrayPtr data) {
    AocArrayPtr return_array = aoc_array_new(sizeof(int));
    char **str = aoc_str_split(aoc_str_array_index(data, 0), "-", 0);
    int start, end;
    start = atoi(str[0]);
    end = atoi(str[1]);

    aoc_int_array_append(return_array, start);
    aoc_int_array_append(return_array, end);

    aoc_str_freev(str);
    return return_array;
}

void *solve_part_1(AocData_t *data) {
    int count = 0;
    int start = aoc_int_array_index(aoc_data_get(data), 0);
    int end = aoc_int_array_index(aoc_data_get(data), 1);

    for (int i = start; i <= end; i++) {
        if (check_rules(i, 1))
            count++;
    }
    return strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    int count = 0;
    int start = aoc_int_array_index(aoc_data_get(data), 0);
    int end = aoc_int_array_index(aoc_data_get(data), 1);

    for (int i = start; i <= end; i++) {
        if (check_rules(i, 2)) {
            count++;
        }
    }
    return strdup_printf("%d", count);
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1); } return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, clean_input);
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
