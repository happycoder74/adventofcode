#ifndef __AOC_STRING_H__
#define __AOC_STRING_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// String functions similar to methods of  python strings
char *str_trim(char *str);
char *str_join(const char *, char **, size_t);
int str_count(char *, char, int, int);
char *substr(char *, int, int);
int str_startswith(char *str, char *start_str);
int str_endswith(char *, char *);
char *strdup_printf(const char *format, ...);

intmax_t getline(char **, size_t *, FILE *);
intmax_t getdelim(char **, size_t *, int, FILE *);
char *stpcpy(char *__restrict__, const char *__restrict__);
char *strdup(const char *str);

#endif /* __AOC_STRING_H__ */

