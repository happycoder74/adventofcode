#include "aoc_regex.h"
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Need to free result in calling function
char *get_match_string(regmatch_t *match_info, const char *string) {
    char      *substring = calloc(strlen(string) + 1, sizeof(char));
    regmatch_t mo = match_info[1];
    unsigned   length = mo.rm_eo - mo.rm_so;
    strncpy(substring, string + mo.rm_so, length);
    substring[length] = '\0';
    return substring;
}

uint32_t regex_match_count(regex_t *pattern, const char *string) {
    regmatch_t match_info[20];
    int        error = 0;
    uint32_t   count = 0;
    uint32_t   offset = 0;

    while (!(error = regexec(pattern, string + offset, 20, match_info, 0))) {
        offset += match_info->rm_eo;
        count++;
    }

    regex_error(error, pattern);

    return count;
}
