#ifndef AOC_REGEX_H
#define AOC_REGEX_H

#include <pcre2posix.h>
#include <stdint.h>

// Macro definitions
#define regex_error(errcode, regex)                                                                                                                                                                    \
    {                                                                                                                                                                                                  \
        char error_string[100];                                                                                                                                                                        \
        if ((errcode) && (errcode != 1)) {                                                                                                                                                             \
            regerror(errcode, regex, error_string, 100);                                                                                                                                               \
            fprintf(stderr, "Regex Error [%d]: (%s) at: %s line %d\n", error, error_string, __FILE__, __LINE__);                                                                                       \
            exit(EXIT_FAILURE);                                                                                                                                                                        \
        }                                                                                                                                                                                              \
    }

/* void     regex_error(int errcode, regex_t *regex); */
char    *get_match_string(regmatch_t *match_info, const char *string);
uint32_t regex_match_count(regex_t *pattern, const char *string);

#endif // !AOC_REGEX_H
