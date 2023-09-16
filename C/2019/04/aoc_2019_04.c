#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"


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

GArray *clean_input(GArray *data) {
    GArray *return_array = g_array_new(TRUE, TRUE, sizeof(int));
    char **str = g_strsplit(g_array_index(data, char *, 0), "-", 0);
    int start, end;
    start = atoi(str[0]);
    end = atoi(str[1]);

    g_array_append_val(return_array, start);
    g_array_append_val(return_array, end);
    
    return return_array;
}

void *solve_part_1(AocData_t *data) {
    int count = 0;
    int start = g_array_index(data->data, int, 0);
    int end = g_array_index(data->data, int, 1);

    for (int i = start; i <= end; i++) {
        if (check_rules(i, 1))
            count++;
    }
    return g_strdup_printf("%d", count);
}

void *solve_part_2(AocData_t *data) {
    int count = 0;
    int start = g_array_index(data->data, int, 0);
    int end = g_array_index(data->data, int, 1);

    for (int i = start; i <= end; i++) {
        if (check_rules(i, 2)) {
            count++;
        }
    }
    return g_strdup_printf("%d", count);
}

void *solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    const int year = 2019;
    const int day = 4;
    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
