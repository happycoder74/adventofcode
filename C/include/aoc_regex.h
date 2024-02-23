#ifndef AOC_REGEX_H
#define AOC_REGEX_H

#include <regex.h>
#include <stdint.h>

void     regex_error(int errcode, regex_t *regex);
char    *get_match_string(regmatch_t *match_info, const char *string);
uint32_t regex_match_count(regex_t *pattern, const char *string);

#endif // !AOC_REGEX_H
