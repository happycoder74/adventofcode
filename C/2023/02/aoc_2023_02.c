#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned red;
    unsigned green;
    unsigned blue;
} Cubes_t;

Cubes_t Bag = {12, 13, 14};

unsigned max_color(const char *str, const char *color) {
    unsigned max_color = 0;
    char    *ptr;
    char    *ptr2;
    ptr = strstr(str, color);
    while (ptr != NULL) {
        unsigned n_color = 0;
        ptr2 = strchr(ptr - 4, ' ') + 1;
        sscanf(ptr2, "%d", &n_color);
        if (n_color > max_color) {
            max_color = n_color;
        }
        if ((ptr + 3) >= (str + strlen(str))) {
            ptr = NULL;
        } else {
            ptr = strstr(ptr + 3, color);
        }
    }

    return max_color;
}

void *solve_part_1(AocData_t *data) {
    unsigned    valid = 0;
    AocArrayPtr input = aoc_data_get(data);

    for (unsigned i = 0; i < input->length; i++) {
        char *str = aoc_str_array_index(input, i);
        if ((max_color(str, "red") <= Bag.red) && (max_color(str, "green") <= Bag.green) && (max_color(str, "blue") <= Bag.blue)) {
            valid += (i + 1);
        }
    }

    return strdup_printf("%d", valid);
}

void *solve_part_2(AocData_t *data) {
    uint32_t sum = 0;

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
    AocData_t *data;

    char sourcefile[20];
    int  year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        if (!strncmp(argv[1], "--test", 6)) {
            data = aoc_data_new_clean("test_input.txt", year, day, NULL);
        } else {
            data = aoc_data_new_clean(argv[1], year, day, NULL);
        }
    } else {
        data = aoc_data_new_clean("input.txt", year, day, NULL);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
