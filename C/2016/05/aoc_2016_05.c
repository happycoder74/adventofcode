#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

#define BUFSIZE 128

char *solve_part_1(char *doorID) {
    guchar to_hash[BUFSIZE];
    const gchar *hashed;
    gint counter = 0;
    gint found = 0;
    GChecksum *checksum;
    gchar *code;

    code = g_strdup("________");
    printf("Part 1:\n");
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

char *solve_part_2(char *doorID) {
    const gchar *hashed;
    gint counter = 0, found = 0;
    gint pos;
    guint j;
    GChecksum *checksum;
    gchar *code;
    guchar to_hash[BUFSIZE];

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


int main(int argc, char **argv) {

    gchar *doorID;

    if (argc > 1) {
        doorID = argv[1];
    } else {
        doorID = "abc";
    }

    TIMER_STR(1, solve_part_1(doorID));
    TIMER_STR(2, solve_part_2(doorID));

}
