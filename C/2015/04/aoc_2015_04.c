#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solution_bin(AocData_t *data, const char *cmp_string) {
    char       string[100];
    int        number = 0;
    GChecksum *checksum = g_checksum_new(G_CHECKSUM_MD5);
    uint8_t    hashcode[100];
    size_t     length;
    bool       found = FALSE;

    char *base = aoc_str_array_index(data->data, 0);

    while (!found) {
        sprintf(string, "%s%d", base, ++number);
        g_checksum_update(checksum, (unsigned char *)string, -1);
        length = 100;
        g_checksum_get_digest(checksum, hashcode, &length);
        if (strlen(cmp_string) == 5) {
            if ((*(hashcode + 0) == 0) && *(hashcode + 1) == 0 && *(hashcode + 2) < 16) {
                found = TRUE;
            }
        } else {
            if ((*(hashcode + 0) == 0) && *(hashcode + 1) == 0 && *(hashcode + 2) == 0) {
                found = TRUE;
            }
        }
        g_checksum_reset(checksum);
    }
    g_checksum_free(checksum);
    return number;
}

void *solve_part_1_bin(AocData_t *data) {
    return strdup_printf("%d", solution_bin(data, "00000"));
}

void *solve_part_2_bin(AocData_t *data) {
    return strdup_printf("%d", solution_bin(data, "000000"));
}

void *solve_all(AocData_t *data) {

    if (data->data) {
        printf("Solving using bin\n");
        timer_func(1, solve_part_1_bin, data, 1);
        timer_func(2, solve_part_2_bin, data, 1);
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
            data = aoc_data_new("test_input.txt", year, day);
        } else {
            data = aoc_data_new(argv[1], year, day);
        }
    } else {
        data = aoc_data_new("input.txt", year, day);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
