#ifndef __AOC_STRING_H__
#define __AOC_STRING_H__

#include <stdio.h>
#include <unistd.h>
#include <glib.h>

// String function macros
#define aoc_str_split(_string, _delimiter, _max_tokens)      (g_strsplit(_string, _delimiter, _max_tokens))

// String functions similar to methods of  python strings
// more to come later
char *str_trim(char *str);
char *str_join(const char *, char **, size_t);
int str_count(char *, char, int, int);
char *substr(char *, int, int);
int str_startswith(char *str, char *start_str);
int str_endswith(char *, char *);
char *strdup_printf(const char *format, ...);

ssize_t getline(char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, int, FILE *);
char *stpcpy(char *__restrict__, const char *__restrict__);
char *strdup(const char *str);
char *strconcat(const char *str1, const char *str2);

void aoc_str_freev(char **);

#endif /* __AOC_STRING_H__ */

