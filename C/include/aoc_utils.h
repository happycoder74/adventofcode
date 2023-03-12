#ifndef __AOC_UTILS_H__
#define __AOC_UTILS_H__

#include <aoc_grid.h>
#include <glib.h>
#include "aoc_timer.h"
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
gboolean aoc_data_hasdata(AocData_t *data);
GArray *aoc_data_data(AocData_t *data);
AocData_t *aoc_data_set_data(AocData_t *aoc, GArray *data);
void aoc_data_free(AocData_t *data);
AocData_t *aoc_data_new2(gchar *filename, int year, int day, GArray *(*clean_function)(GArray *));

gboolean is_horisontal(Line);
gboolean is_vertical(Line);
void print_line(Line);
Point point_difference(Point, Point);
guint point_hash(gconstpointer);
gboolean point_equal(gconstpointer, gconstpointer);

GSList *get_input_list(char *filename, int year, int day);
GArray *get_input(char *filename, int year, int day);
GArray *get_input_new(char *filename, int year, int day);
gint max(gint *, gint);
gint min(gint *, gint);
gint min_non_zero(gint *, gint);

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

#endif
