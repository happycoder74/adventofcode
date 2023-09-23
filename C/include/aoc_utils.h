#ifndef __AOC_UTILS_H__
#define __AOC_UTILS_H__

#include <stdbool.h>

#include <glib.h>
#include "aoc_array.h"
#include "aoc_types.h"

#define g_array_length(X) (X->len)

typedef struct point {
    int x;
    int y;
} Point;

typedef struct line {
    Point p0;
    Point p1;
    int stepx;
    int stepy;
} Line;

// Allocation functions
AocData_t *aoc_data_new(gchar *filename, int year, int day);
size_t aoc_data_length(AocData_t *data);
bool aoc_data_hasdata(AocData_t *data);
AocArrayPtr aoc_data_data(AocData_t *data);
AocData_t *aoc_data_set_data(AocData_t *aoc, AocArrayPtr data);
void aoc_data_free(AocData_t *data);
AocData_t *aoc_data_new_clean(gchar *filename, int year, int day, AocArrayPtr(*clean_function)(AocArrayPtr));

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
void line_array_print(GArray *lines);
int line_length(Line);

Point *line_intersection(Line line1, Line line2, Point *intersection_point);
Point point_difference(Point, Point);
guint point_hash(gconstpointer);
gboolean point_equal(gconstpointer, gconstpointer);
int point_manhattan_distance(Point, Point);
int point_distance(Point, Point);
bool point_on_line(Point p, Line line);

GSList *get_input_list(char *filename, int year, int day);
AocArrayPtr get_input(char *filename, int year, int day);
AocArrayPtr get_input_new(char *filename, int year, int day);
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

char *_aoc_basename(const char *path, const char pathsep);
#if (defined(__WIN32__) && !defined(__MINGW32__))
#define aoc_basename(X) _aoc_basename(X, '\\');
#else
#define aoc_basename(X) _aoc_basename(X, '/');
#endif

#endif
