#ifndef __AOC_STRING_H__
#define __AOC_STRING_H__

#include <stdlib.h>

// String functions similar to methods of  python strings
char *str_trim(char *str);
char *str_join(const char *, char **, size_t);
int str_count(char *, char, int, int);
char *substr(char *, int, int);
int str_startswith(char *str, char *start_str);
int str_endswith(char *, char *);
char *strdup_printf(char *format, ...);

#ifdef __MINGW32__
#include <stdio.h>
ssize_t getline(char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, int, FILE *);
char *stpcpy(char *__restrict__, const char *__restrict__);
#endif

#endif /* __AOC_STRING_H__ */

