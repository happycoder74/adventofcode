#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_timer.h"
#include "aoc_array.h"
#include "aoc_string.h"

#define BUFSIZE 128

void *solve_part_1(AocData_t *data) {
    unsigned char to_hash[BUFSIZE];
    const char *hashed;
    int counter = 0;
    int found = 0;
    char code[] = "________";
    char *doorID;
    int count = 0;
    GChecksum *checksum;

    doorID = aoc_str_array_index(aoc_data_get(data), 0);

    printf("Part 1:\n");
    printf("\t%s\r", code);
    while ((found < 8) && (count < 5)){
        snprintf((char*)to_hash, BUFSIZE, "%s%d", doorID, counter++);
        checksum = g_checksum_new(G_CHECKSUM_MD5);
        g_checksum_update(checksum, to_hash, strlen((const char *)to_hash));
        hashed = g_checksum_get_string(checksum);
        if (((hashed[0] == '0') &&
            (hashed[1] == '0') &&
            (hashed[2] == '0') &&
            (hashed[3] == '0') &&
            (hashed[4] == '0'))) {
            code[found++] = hashed[5];
            printf("\t%s\r", code);
            fflush(stdout);
        }
    }
    printf("\n");
    return strdup_printf("%s (%d)", code, counter);
}

static int digit_value(char c) {
    if (!isdigit(c))
        return -1;
    return c - '0';
}

void *solve_part_2(AocData_t *data) {
    const char *hashed;
    int counter = 0, found = 0;
    int pos;
    unsigned int j;
    GChecksum *checksum;
    char code[] = "________";
    unsigned char to_hash[BUFSIZE];
    char *doorID;

    doorID = aoc_str_array_index(aoc_data_get(data), 0);

    printf("\nPart 2:\n");
    found = 0;
    counter = 0;

    while (found < 8) {
        snprintf((char *)to_hash, BUFSIZE, "%s%d", doorID, counter++);
        checksum = g_checksum_new(G_CHECKSUM_MD5);
        g_checksum_update(checksum, to_hash, strlen((const char *)to_hash));
        hashed = g_checksum_get_string(checksum);
        if (!strncasecmp(hashed, "00000", 5)) {
            if ((pos = digit_value(hashed[5])) != -1) {
                if ((pos < 8) && (code[pos] == '_')) {
                    found++;
                    code[pos] = hashed[6];
                }
            }
        }
        if ((((counter - 1) % 100000) == 0) || (found == 8)) {
            printf("\t");
            for (j = 0; j < strlen(code); j++) {
                if (code[j] == '_') {
                    printf("\033[1;32m%x\033[0m", (0 + rand() % 16));
                } else {
                    printf("\033[1;33m%c\033[0m", code[j]);
                }
            }
            printf("\r");
            fflush(stdout);
        }
        g_checksum_free(checksum);
    }
    printf("\n");
    return strdup(code);
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
    int year, day;

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
