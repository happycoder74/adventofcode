#ifndef __AOC_UTILS_H__
#define __AOC_UTILS_H__

#include <glib.h>

#define TIMER(part, func, TYPE, show_res) TIMER_##TYPE(part, func, show_res)

#define TIMER_INT(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        int result = func; \
        g_timer_stop(timer); \
        gdouble elapsed, elapsed_unit; \
        elapsed = g_timer_elapsed(timer, NULL); \
		elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer: %d\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)

#define TIMER_STR(part, func, show_res) \
    do { \
        GTimer *timer = g_timer_new(); \
        gchar *result = func; \
        g_timer_stop(timer); \
        gdouble elapsed, elapsed_unit; \
        elapsed = g_timer_elapsed(timer, NULL); \
		elapsed_unit = elapsed > 0.1 ? elapsed : elapsed*1000; \
		if (show_res) { \
			printf("Part %d answer:%s\r\033[35C( %6.3lf %-2s )\n", \
                    part, result, elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} else { \
			printf("Time elapsed:\r\033[35C( %6.3lf %-2s )\n",\
                    elapsed_unit, elapsed > 0.1? "s":"ms"); \
		} \
        g_timer_destroy(timer); \
    } while (0)


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

typedef struct {
    int *grid;
    int rows;
    int columns;
} Grid;

gboolean is_horisontal(Line);
gboolean is_vertical(Line);
void print_line(Line);
Point point_difference(Point, Point);
guint point_hash(gconstpointer);
gboolean point_equal(gconstpointer, gconstpointer);
Grid *grid_new(int rows, int columns);
int grid_index(Grid *grid, int row, int column);
void grid_index_set(Grid *grid, int row, int column, int value);

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

#endif // __AOC_UTILS_H__
