#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

#define BUFSIZE 128

char *solve_part_1(GArray *data) {
    guchar to_hash[BUFSIZE];
    const gchar *hashed;
    gint counter = 0;
    gint found = 0;
    GChecksum *checksum;
    gchar *code;
    gchar *doorID;

    doorID = g_array_index(data, gchar *, 0);

    code = g_strdup("________");
    printf("Part 1:\n");
    printf("%s\r", code);
    while (found < 8) {
        g_snprintf((gchar*)to_hash, BUFSIZE, "%s%d", doorID, counter++);
        checksum = g_checksum_new(G_CHECKSUM_MD5);
        g_checksum_update(checksum, to_hash, strlen((const gchar*)to_hash));
        hashed = g_checksum_get_string(checksum);
        if (!g_ascii_strncasecmp(hashed, "00000", 5)) {
            code[found++] = hashed[5];
            printf("%s\r", code);
            fflush(stdout);
        }
        g_checksum_free(checksum);
    }
    printf("\n");
    return code;
}

char *solve_part_2(GArray *data) {
    const gchar *hashed;
    gint counter = 0, found = 0;
    gint pos;
    guint j;
    GChecksum *checksum;
    gchar *code;
    guchar to_hash[BUFSIZE];
    char *doorID;

    doorID = g_array_index(data, char *, 0);

    printf("\nPart 2:\n");
    found = 0;
    counter = 0;
    code = g_strdup("________");

    while (found < 8) {
        g_snprintf((gchar *)to_hash, BUFSIZE, "%s%d", doorID, counter++);
        checksum = g_checksum_new(G_CHECKSUM_MD5);
        g_checksum_update(checksum, to_hash, strlen((const gchar *)to_hash));
        hashed = g_checksum_get_string(checksum);
        if (!g_ascii_strncasecmp(hashed, "00000", 5)) {
            if ((pos = g_ascii_digit_value(hashed[5])) != -1) {
                if ((pos < 8) && (code[pos] == '_')) {
                    found++;
                    code[pos] = hashed[6];
                }
            }
        }
        if ((((counter - 1) % 1000) == 0) || (found == 8)) {
            for (j = 0; j < strlen(code); j++) {
                if (code[j] == '_') {
                    printf("%x", (0 + rand() % 16));
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
    return code;
}


int solve_all(char *filename, int year, int day) {
    GArray *data;

    data = get_input(filename, year, day);

    if (data) {
        TIMER(1, solve_part_1(data), STR, 1);
        TIMER(2, solve_part_2(data), STR, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2016, 5), INT, 0);

    g_free(filename);
    return 0;
}
