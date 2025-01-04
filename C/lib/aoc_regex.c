#include "aoc_regex.h"
#include "aoc_string.h"
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
    regmatch_t match_info;
    int        error = 0;
    uint32_t   count = 0;
    uint32_t   offset = 0;

    while (!(error = regexec(pattern, string + offset, 1, &match_info, 0))) {
        offset += match_info.rm_eo;
        count++;
    }

    return count;
}

/*
 * char **regex_split(const char *pattern, const char *string, unsigned n_splits)
 *
 * pattern: PCRE2 valid regex pattern
 * string:  Null terminated string to be split by regex
 * n_splits: Number of splits to return. If n_splits == 0, return a full split.
 *
 * RETURN VALUE
 * returns a pointer to a NULL terminated array of null-terminated strings.
 * The ownership of the returned array and the strings within the array is transfered to the caller
 *
 * The memory should be released by the caller using 'aoc_str_freev'
 */

char **regex_split(const char *pattern, const char *string, unsigned n_splits) {
    regex_t    re;
    int        error;
    regmatch_t match;
    unsigned   split_len = 11;

    char **split_string = calloc(n_splits > 0 ? n_splits + 1 : split_len, sizeof(char *));
    if (string == NULL) {
        return split_string;
    }

    error = regcomp(&re, pattern, 0);
    if (error) {
        free(split_string);
        return NULL;
    }

    unsigned i_split = 0;
    unsigned offset = 0;
    error = regexec(&re, string + offset, 1, &match, 0);
    while (!error) {
        split_string[i_split++] = strndup(string + offset, match.rm_so);
        if (n_splits == 0) {
            if (i_split == split_len - 1) {
                split_len *= 2;
                char **new_split_string = realloc(split_string, split_len);
                if (new_split_string == NULL) {
                    fprintf(stderr, "Could not re-allocate array\n");
                    split_string[i_split] = NULL;
                    return split_string;
                } else {
                    split_string = new_split_string;
                }
            }
        } else {
            if (i_split == n_splits - 1) {
                split_string[i_split] = NULL;
                return split_string;
            }
        }
        offset += match.rm_eo;
        error = regexec(&re, string + offset, 1, &match, 0);
    }

    if (*(string + offset) != '\0') {
        split_string[i_split] = strndup(string + offset, strlen(string) - offset);
    }

    return split_string;
}
