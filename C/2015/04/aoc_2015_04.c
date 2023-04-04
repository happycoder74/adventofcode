#include <corecrt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "glib.h"
#include "aoc_utils.h"
#include "aoc_string.h"

GArray *clean_input(GArray *data) { return data; }

int solution_str(AocData_t *data, const char *cmp_string) {
    int number = 0;
    GChecksum *checksum = g_checksum_new(G_CHECKSUM_MD5);
    char *string = NULL;
    const char *hashcode;
    char *base = g_array_index(data->data, char *, 0);

    while (TRUE) {
        string = strdup_printf("%s%d", base, ++number);
        g_checksum_update(checksum, (guchar *)string, -1);
        hashcode = g_checksum_get_string(checksum);
        free(string);
        if (strncmp(hashcode, cmp_string, strlen(cmp_string)) == 0) {
            break;
        }
        g_checksum_reset(checksum);
    }
    g_checksum_free(checksum);
    return number;
}

int solution_bin(AocData_t *data, const char *cmp_string) {
    char string[100];
    int number = 0;
    GChecksum *checksum = g_checksum_new(G_CHECKSUM_MD5);
    uint8_t hashcode[100];
    size_t length;
    bool found = FALSE;

    char *base = g_array_index(data->data, char *, 0);

    while (!found) {
        sprintf(string, "%s%d", base, ++number);
        g_checksum_update(checksum, (guchar *)string, -1);
        length = 100;
        g_checksum_get_digest(checksum, hashcode, &length);
        if (strlen(cmp_string) == 5) {
            if ((*(hashcode + 0) == 0) && *(hashcode + 1) == 0 &&
                *(hashcode + 2) < 16) {
                found = TRUE;
            }
        } else {
            if ((*(hashcode + 0) == 0) && *(hashcode + 1) == 0 &&
                *(hashcode + 2) == 0) {
                found = TRUE;
            }
        }
        g_checksum_reset(checksum);
    }
    g_checksum_free(checksum);
    return number;
}

void *solve_part_1_str(AocData_t *data) {
    return strdup_printf("%d", solution_str(data, "00000"));
}

void *solve_part_2_str(AocData_t *data) {
    return strdup_printf("%d", solution_str(data, "000000"));
}

void *solve_part_1_bin(AocData_t *data) {
    return strdup_printf("%d", solution_bin(data, "00000"));
}

void *solve_part_2_bin(AocData_t *data) {
    return strdup_printf("%d", solution_bin(data, "000000"));
}

void *solve_all(AocData_t *data) {

    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1_str, data, 1);
        timer_func(2, solve_part_2_str, data, 1);
        timer_func(1, solve_part_1_bin, data, 1);
        timer_func(2, solve_part_2_bin, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    char *sourcefile;
    int year, day;

    sourcefile = basename(__FILE__);
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);

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
