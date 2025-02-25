#ifndef __AOC_STRING_H__
#define __AOC_STRING_H__

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// String function macros
#define aoc_str_split(_string, _delimiter, _max_tokens)                                            \
    (str_split(_string, _delimiter, _max_tokens))

// String functions similar to methods of  python strings
// more to come later
char  *str_trim(char *str);
char  *str_join(const char *, char **, size_t);
int    str_count(char *, char, int, int);
char  *substr(char *, int, int);
int    str_startswith(char *str, char *start_str);
int    str_endswith(char *, char *);
char  *strdup_printf(const char *format, ...);
char  *strdup_vprintf(const char *format, va_list args);
char **str_split(const char *string, const char *delimiter, uint32_t max_tokens);

ssize_t getline(char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, int, FILE *);
char   *aoc_stpcpy(char *__restrict__, const char *__restrict__);
// char   *strdup(const char *str);
// char   *strndup(const char *str, size_t n);
char   *strconcat(const char *str1, const char *str2);

void aoc_str_freev(char **);

#endif /* __AOC_STRING_H__ */
