#ifndef __AOC_IO_H__
#define __AOC_IO_H__

#include "aoc_types.h"

int         download_input(int year, int day);
AocSList   *get_input_list(char *filename, int year, int day);
AocArrayPtr get_input(char *filename, int year, int day);
AocArrayPtr get_input_new(char *filename, int year, int day);

#ifdef __MINGW32__
#include <stdio.h>
ssize_t getline(char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, int, FILE *);
#endif

#endif
