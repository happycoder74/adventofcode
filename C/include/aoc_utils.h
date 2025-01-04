#ifndef __AOC_UTILS_H__
#define __AOC_UTILS_H__

#include "aoc_types.h"
#include <stdbool.h>
//
// aoc_timer.h and aoc_array.h included for legacy support
// will be removed when all solutions are converted

// AoC Data Structure macros
#define aoc_data_new(filename, year, day) (aoc_data_new_clean(filename, year, day, NULL))
#define aoc_data_get(arr)                 (((arr)->data != NULL) && (arr != NULL) ? ((arr)->data) : NULL)
#define aoc_data_length(arr)              (((arr)->data != NULL) && (arr != NULL) ? (arr)->data->length : 0)
#define aoc_data_has_data(arr)            ((arr)->data != NULL ? 1 : 0)

// AoC Data Structure functions
AocData_t *aoc_data_set_data(AocData_t *aoc, AocArrayPtr data);
void       aoc_data_free(AocData_t *data);
AocData_t *aoc_data_new_clean(char *filename, int year, int day, AocArrayPtr (*clean_function)(AocArrayPtr));
AocData_t *get_data(int argc, char **argv, unsigned year, unsigned day, AocArrayPtr(parse_func)(AocArrayPtr));

bool   is_horisontal(Line);
bool   is_vertical(Line);
bool   is_diagonal(Line);
bool   is_parallel(Line, Line);
void   print_line(Line);
void   line_print(Line line);
Line   line_new(Point, Point);
Point *point_new_m(int, int);
Point  point_new(int, int);
void   point_print(Point);
char  *point_to_string(Point, char *, unsigned);
void   line_array_print(AocArrayPtr lines);
int    line_length(Line);

Point       *line_intersection(Line line1, Line line2, Point *intersection_point);
Point        point_difference(Point, Point);
unsigned int point_hash(const void *);
int          point_equal(const void *, const void *);
int          point_manhattan_distance(Point, Point);
int          point_distance(Point, Point);
bool         point_on_line(Point p, Line line);
void         point_move(Point *p, Point delta);

#ifdef MIN
#undef MIN
#endif
#define MIN(_X_, _Y_) (((_X_) < (_Y_)) ? (_X_) : (_Y_))
#ifdef MAX
#undef MAX
#endif
#define MAX(_X_, _Y_) (((_X_) > (_Y_)) ? (_X_) : (_Y_))

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

// Legacy support functions
// Returns max and min value in integer array
int max(int *, int);
int min(int *, int);
// End of legacy support functions

int int_array_max(int *, int);
int int_array_min(int *, int);
int min_non_zero(int *, int);

// Other utility functions and macros
char *basename(const char *);
char *basename_new(const char *);
#define aoc_basename(X) (basename_new(X))

#endif
