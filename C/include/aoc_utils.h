#ifndef __AOC_UTILS_H__
#define __AOC_UTILS_H__

#include <stdbool.h>
#include "aoc_types.h"
//
// aoc_timer.h and aoc_array.h included for legacy support
// will be removed when all solutions are converted

// AoC Data Structure macros
#define aoc_data_new(filename, year, day)       (aoc_data_new_clean(filename, year, day, NULL))
#define aoc_data_get(arr)                      (((arr)->data != NULL) && (arr != NULL) ? ((arr)->data) : NULL)
#define aoc_data_length(arr)                    (((arr)->data != NULL) && (arr != NULL) ? (arr)->data->length : 0)
#define aoc_data_has_data(arr)                  ((arr)->data != NULL ? 1 : 0)

// AoC Data Structure functions
AocData_t *aoc_data_set_data(AocData_t *aoc, AocArrayPtr data);
void aoc_data_free(AocData_t *data);
AocData_t *aoc_data_new_clean(char *filename, int year, int day, AocArrayPtr (*clean_function)(AocArrayPtr));

bool is_horisontal(Line);
bool is_vertical(Line);
bool is_diagonal(Line);
bool is_parallel(Line, Line);
void print_line(Line);
void line_print(Line line);
Line line_new(Point, Point);
Point *point_new_m(int, int);
Point point_new(int, int);
void point_print(Point);
char *point_to_string(Point, char *);
void line_array_print(AocArrayPtr lines);
int line_length(Line);

Point *line_intersection(Line line1, Line line2, Point *intersection_point);
Point point_difference(Point, Point);
unsigned int point_hash(const void *);
int point_equal(const void *, const void *);
int point_manhattan_distance(Point, Point);
int point_distance(Point, Point);
bool point_on_line(Point p, Line line);

AocSList *get_input_list(char *filename, int year, int day);
AocArrayPtr get_input(char *filename, int year, int day);
AocArrayPtr get_input_new(char *filename, int year, int day);

// Legacy support functions
// Returns max and min value in integer array
int max(int *, int);
int min(int *, int);
// End of legacy support functions

int int_array_max(int *, int);
int int_array_min(int *, int);
int min_non_zero(int *, int);

// String functions similar to methods of  python strings
char *str_trim(char *str);
char *str_join(const char *, char **, size_t);
int str_count(char *, char, int, int);
char *substr(char *, int, int);
int str_startswith(char *str, char *start_str);
int str_endswith(char *, char *);

#ifdef __MINGW32__
#include <stdio.h>
ssize_t getline(char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, int, FILE *);
char *stpcpy(char *__restrict__, const char *__restrict__);
#endif

// Other utility functions and macros
char *basename(const char *);
char *basename_new(const char *);
#define aoc_basename(X)         (basename_new(X))

#endif
