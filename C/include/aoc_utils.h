#ifndef __AOC_UTILS_H__
#define __AOC_UTILS_H__

#include <aoc_timer.h>
#include <aoc_grid.h>
#include <glib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point p0;
    Point p1;
    int stepx;
    int stepy;
} Line;

gboolean is_horisontal(Line);
gboolean is_vertical(Line);
void print_line(Line);
Point point_difference(Point, Point);
guint point_hash(gconstpointer);
gboolean point_equal(gconstpointer, gconstpointer);

GArray *get_input(char *, int, int);
GArray *get_input_new(char *, int, int);
gint max(gint *, gint);
gint min(gint *, gint);
gint min_non_zero(gint *, gint);

// String functions similar to methods of  python strings
char *str_trim(char *str);
char *str_join(const char *, char **, size_t);
int str_count(char *, char, int, int);
char *substr(char *, int, int);
int str_startswith(char *, char *);
int str_endswith(char *, char *);

#ifdef __MINGW32__
#include <stdio.h>
ssize_t getline(char **, size_t *, FILE *);
ssize_t getdelim(char **, size_t *, int, FILE *);
char *stpcpy(char *__restrict__, const char *__restrict__);
#endif

#endif
